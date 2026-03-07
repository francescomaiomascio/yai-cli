/* SPDX-License-Identifier: Apache-2.0 */
#define _POSIX_C_SOURCE 200809L

#include "yai_cli/lifecycle.h"

#include <yai_sdk/client.h>
#include <yai_sdk/errors.h>
#include <yai_sdk/paths.h>

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static void reply_set(
    yai_sdk_reply_t *r,
    const char *status,
    const char *code,
    const char *reason,
    const char *command_id,
    const char *summary,
    const char *hint_1,
    const char *hint_2)
{
  if (!r) return;
  memset(r, 0, sizeof(*r));
  snprintf(r->status, sizeof(r->status), "%s", status ? status : "error");
  snprintf(r->code, sizeof(r->code), "%s", code ? code : "INTERNAL_ERROR");
  snprintf(r->reason, sizeof(r->reason), "%s", reason ? reason : "internal_error");
  snprintf(r->command_id, sizeof(r->command_id), "%s", command_id ? command_id : "yai.unknown.unknown");
  snprintf(r->summary, sizeof(r->summary), "%s", summary ? summary : "");
  if (hint_1 && hint_1[0]) {
    snprintf(r->hints[0], sizeof(r->hints[0]), "%s", hint_1);
    r->hint_count = 1;
  }
  if (hint_2 && hint_2[0]) {
    snprintf(r->hints[1], sizeof(r->hints[1]), "%s", hint_2);
    r->hint_count = 2;
  }
  snprintf(r->target_plane, sizeof(r->target_plane), "%s", "root");
}

static void sleep_ms(long ms)
{
  struct timespec ts;
  if (ms <= 0) return;
  ts.tv_sec = ms / 1000;
  ts.tv_nsec = (ms % 1000) * 1000000L;
  while (nanosleep(&ts, &ts) != 0 && errno == EINTR) {}
}

static int runtime_is_up(void)
{
  yai_sdk_client_t *client = NULL;
  yai_sdk_client_opts_t opts = {.ws_id = "default", .arming = 1, .role = "operator", .auto_handshake = 0};
  int rc = yai_sdk_client_open(&client, &opts);
  if (rc != YAI_SDK_OK) return 0;
  yai_sdk_client_close(client);
  return 1;
}

static int spawn_boot_detached(void)
{
  char boot_bin[1024];
  pid_t pid;
  if (yai_path_boot_bin(boot_bin, sizeof(boot_bin)) != 0 || !boot_bin[0]) {
    return YAI_SDK_IO;
  }

  pid = fork();
  if (pid < 0) return YAI_SDK_IO;
  if (pid == 0)
  {
    int devnull;
    (void)setsid();
    devnull = open("/dev/null", O_RDWR);
    if (devnull >= 0) {
      (void)dup2(devnull, STDIN_FILENO);
      (void)dup2(devnull, STDOUT_FILENO);
      (void)dup2(devnull, STDERR_FILENO);
      if (devnull > STDERR_FILENO) (void)close(devnull);
    }
    execl(boot_bin, boot_bin, "--master", (char *)NULL);
    _exit(127);
  }
  return YAI_SDK_OK;
}

static int terminate_pidfile(const char *pidfile)
{
  FILE *f;
  char line[64];
  long pid_long;
  pid_t pid;
  if (!pidfile || !pidfile[0]) return 0;
  f = fopen(pidfile, "r");
  if (!f) return 0;
  if (!fgets(line, sizeof(line), f)) {
    fclose(f);
    return 0;
  }
  fclose(f);
  pid_long = strtol(line, NULL, 10);
  if (pid_long <= 1) return 0;
  pid = (pid_t)pid_long;
  if (kill(pid, SIGTERM) == 0 || errno == ESRCH) return 1;
  return 0;
}

static int terminate_stack_processes(void)
{
  char runtime_home[1024];
  char pidfile[1280];
  const char *candidates[] = {
    "root/root.pid",
    "kernel/kernel.pid",
    "engine/engine.pid",
    "boot/boot.pid",
    "dev/daemon.pid"
  };
  int terminated = 0;
  size_t i;

  if (yai_path_runtime_home(runtime_home, sizeof(runtime_home)) != 0) {
    return 0;
  }

  for (i = 0; i < (sizeof(candidates) / sizeof(candidates[0])); i++) {
    if (snprintf(pidfile, sizeof(pidfile), "%s/%s", runtime_home, candidates[i]) <= 0) continue;
    terminated += terminate_pidfile(pidfile);
  }
  return terminated;
}

static int run_up(yai_sdk_reply_t *out)
{
  if (runtime_is_up()) {
    reply_set(out, "ok", "OK", "lifecycle_up_already_running", "yai.lifecycle.up",
              "Runtime stack is already running.", NULL, NULL);
    return YAI_SDK_OK;
  }
  if (spawn_boot_detached() != YAI_SDK_OK) {
    reply_set(out, "error", "SERVER_UNAVAILABLE", "lifecycle_up_spawn_failed", "yai.lifecycle.up",
              "Unable to start runtime stack.",
              "Set YAI_BOOT_BIN or YAI_INSTALL_ROOT and retry.",
              "Run: yai doctor runtime");
    return YAI_SDK_SERVER_OFF;
  }
  for (int i = 0; i < 120; i++) {
    if (runtime_is_up()) {
      reply_set(out, "ok", "OK", "lifecycle_up_started", "yai.lifecycle.up",
                "Runtime stack started.", NULL, NULL);
      return YAI_SDK_OK;
    }
    sleep_ms(100);
  }
  reply_set(out, "error", "RUNTIME_NOT_READY", "lifecycle_up_timeout", "yai.lifecycle.up",
            "Runtime is up but not ready for control calls.",
            "Try: yai root handshake_status",
            "Run: yai doctor runtime");
  return YAI_SDK_RUNTIME_NOT_READY;
}

static int run_down(yai_sdk_reply_t *out)
{
  char root_sock[1024];
  (void)terminate_stack_processes();
  sleep_ms(200);
  if (yai_path_root_sock(root_sock, sizeof(root_sock)) == 0) (void)unlink(root_sock);
  reply_set(out, "ok", "OK", "lifecycle_down_completed", "yai.lifecycle.down",
            "Runtime stack stop signal delivered.", NULL, NULL);
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
    if (rc == 0) {
      reply_set(out, "ok", "OK", "lifecycle_restart_completed", "yai.lifecycle.restart",
                "Runtime stack restarted.", NULL, NULL);
    }
    return rc;
  }
  return YAI_SDK_BAD_ARGS;
}
