/* SPDX-License-Identifier: Apache-2.0 */
#define _POSIX_C_SOURCE 200809L

#include "yai_cli/porcelain/lifecycle.h"

#include <yai_sdk/client.h>
#include <yai_sdk/errors.h>
#include <yai_sdk/paths.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>

static void reply_set(yai_sdk_reply_t *r, const char *status, const char *code, const char *reason, const char *command_id)
{
  if (!r) return;
  memset(r, 0, sizeof(*r));
  snprintf(r->status, sizeof(r->status), "%s", status ? status : "error");
  snprintf(r->code, sizeof(r->code), "%s", code ? code : "INTERNAL_ERROR");
  snprintf(r->reason, sizeof(r->reason), "%s", reason ? reason : "internal_error");
  snprintf(r->command_id, sizeof(r->command_id), "%s", command_id ? command_id : "yai.unknown.unknown");
  snprintf(r->target_plane, sizeof(r->target_plane), "%s", "root");
}

static void sleep_ms(long ms)
{
  if (ms <= 0) return;
  struct timespec ts;
  ts.tv_sec = ms / 1000;
  ts.tv_nsec = (ms % 1000) * 1000000L;
  while (nanosleep(&ts, &ts) != 0 && errno == EINTR) {}
}

static int runtime_is_up(void)
{
  yai_sdk_client_t *client = NULL;
  yai_sdk_client_opts_t opts = {.ws_id = "default", .arming = 1, .role = "operator", .auto_handshake = 1};
  int rc = yai_sdk_client_open(&client, &opts);
  if (rc != YAI_SDK_OK) return 0;
  yai_sdk_client_close(client);
  return 1;
}

static int spawn_boot_detached(void)
{
  pid_t pid = fork();
  if (pid < 0) return YAI_SDK_IO;
  if (pid == 0)
  {
    (void)setsid();
    int devnull = open("/dev/null", O_RDWR);
    if (devnull >= 0) {
      (void)dup2(devnull, STDIN_FILENO);
      (void)dup2(devnull, STDOUT_FILENO);
      (void)dup2(devnull, STDERR_FILENO);
      if (devnull > STDERR_FILENO) (void)close(devnull);
    }
    const char *env_boot = getenv("YAI_BOOT_BIN");
    if (env_boot && env_boot[0]) execl(env_boot, env_boot, "--master", (char *)NULL);
    execlp("yai-boot", "yai-boot", "--master", (char *)NULL);
    execl("../yai/build/bin/yai-boot", "../yai/build/bin/yai-boot", "--master", (char *)NULL);
    execl("../yai/dist/bin/yai-boot", "../yai/dist/bin/yai-boot", "--master", (char *)NULL);
    _exit(127);
  }
  return YAI_SDK_OK;
}

static void terminate_stack_processes(void)
{
  (void)system("pkill -TERM -f yai-root-server >/dev/null 2>&1 || true");
  (void)system("pkill -TERM -f yai-kernel >/dev/null 2>&1 || true");
  (void)system("pkill -TERM -f yai-engine >/dev/null 2>&1 || true");
  (void)system("pkill -TERM -f yai-boot >/dev/null 2>&1 || true");
}

static int run_up(yai_sdk_reply_t *out)
{
  if (runtime_is_up()) {
    reply_set(out, "ok", "OK", "lifecycle_up_already_running", "yai.lifecycle.up");
    return YAI_SDK_OK;
  }
  if (spawn_boot_detached() != YAI_SDK_OK) {
    reply_set(out, "error", "INTERNAL_ERROR", "lifecycle_up_spawn_failed", "yai.lifecycle.up");
    return YAI_SDK_IO;
  }
  for (int i = 0; i < 50; i++) {
    if (runtime_is_up()) {
      reply_set(out, "ok", "OK", "lifecycle_up_started", "yai.lifecycle.up");
      return YAI_SDK_OK;
    }
    sleep_ms(100);
  }
  reply_set(out, "error", "RUNTIME_NOT_READY", "lifecycle_up_timeout", "yai.lifecycle.up");
  return YAI_SDK_RUNTIME_NOT_READY;
}

static int run_down(yai_sdk_reply_t *out)
{
  terminate_stack_processes();
  sleep_ms(200);
  char root_sock[512];
  if (yai_path_root_sock(root_sock, sizeof(root_sock)) == 0) (void)unlink(root_sock);
  reply_set(out, "ok", "OK", "lifecycle_down_completed", "yai.lifecycle.down");
  return YAI_SDK_OK;
}

int yai_cli_lifecycle_run(const char *command_id, yai_sdk_reply_t *out)
{
  if (!command_id || !out) return YAI_SDK_BAD_ARGS;
  if (strcmp(command_id, "yai.lifecycle.up") == 0) return run_up(out);
  if (strcmp(command_id, "yai.lifecycle.down") == 0) return run_down(out);
  if (strcmp(command_id, "yai.lifecycle.restart") == 0) {
    int rc = run_down(out);
    if (rc != 0) return rc;
    rc = run_up(out);
    if (rc == 0) reply_set(out, "ok", "OK", "lifecycle_restart_completed", "yai.lifecycle.restart");
    return rc;
  }
  return YAI_SDK_BAD_ARGS;
}
