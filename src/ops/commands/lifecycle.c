/* SPDX-License-Identifier: Apache-2.0 */
// src/ops/commands/lifecycle.c

#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 200809L

#include <yai_cli/ops/ops.h>
#include <yai_cli/paths.h>
#include <yai_cli/rpc/rpc.h>
#include <yai_protocol_ids.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <stdint.h>

#define YAI_OK 0
#define WAIT_RETRIES 20
#define WAIT_INTERVAL_US 200000

enum { YAI_CLI_RPC_RESP_MAX = 4096 };

static int root_socket_exists(void)
{
    char sock[512];
    if (yai_path_root_sock(sock, sizeof(sock)) != 0)
        return -1;

    struct stat st;
    return (stat(sock, &st) == 0) ? YAI_OK : -1;
}

static int wait_for_root_ready(void)
{
    for (int i = 0; i < WAIT_RETRIES; i++) {
        if (root_socket_exists() == YAI_OK)
            return YAI_OK;
        usleep(WAIT_INTERVAL_US);
    }
    return -1;
}

static int kernel_socket_exists(void)
{
    const char *home = getenv("HOME");
    if (!home || !home[0])
        return -1;

    char sock[512];
    int n = snprintf(sock, sizeof(sock), "%s/.yai/run/kernel/control.sock", home);
    if (n <= 0 || (size_t)n >= sizeof(sock))
        return -1;

    struct stat st;
    return (stat(sock, &st) == 0) ? YAI_OK : -1;
}

static int wait_for_kernel_ready(void)
{
    for (int i = 0; i < WAIT_RETRIES; i++) {
        if (kernel_socket_exists() == YAI_OK)
            return YAI_OK;
        usleep(WAIT_INTERVAL_US);
    }
    return -1;
}

static int resolve_bin(char *out, size_t cap, const char *name)
{
    const char *env_bin = NULL;
    if (strcmp(name, "yai-boot") == 0) {
        env_bin = getenv("YAI_BOOT_BIN");
    } else if (strcmp(name, "yai-engine") == 0) {
        env_bin = getenv("YAI_ENGINE_BIN");
    }

    if (env_bin && env_bin[0] && access(env_bin, X_OK) == 0) {
        int n = snprintf(out, cap, "%s", env_bin);
        return (n > 0 && (size_t)n < cap) ? 0 : -1;
    }

    const char *home = getenv("HOME");
    if (!home) return -1;

    int n = snprintf(out, cap, "%s/.yai/artifacts/yai-core/bin/%s", home, name);
    if (n > 0 && (size_t)n < cap && access(out, X_OK) == 0)
        return 0;

    n = snprintf(out, cap, "%s/Developer/YAI/yai/build/bin/%s", home, name);
    if (n > 0 && (size_t)n < cap && access(out, X_OK) == 0)
        return 0;

    char which_cmd[256];
    snprintf(which_cmd, sizeof(which_cmd), "command -v %s", name);
    FILE *fp = popen(which_cmd, "r");
    if (!fp) return -1;
    if (!fgets(out, (int)cap, fp)) {
        pclose(fp);
        return -1;
    }
    pclose(fp);

    size_t len = strlen(out);
    while (len > 0 && (out[len - 1] == '\n' || out[len - 1] == '\r')) {
        out[--len] = '\0';
    }

    return (len > 0 && access(out, X_OK) == 0) ? 0 : -1;
}

static int is_help_arg(const char *a)
{
    return a && (strcmp(a, "-h") == 0 || strcmp(a, "--help") == 0 || strcmp(a, "help") == 0);
}

static void up_usage(void)
{
    printf("Usage:\n");
    printf("  yai up [--ws <id>] [--detach] [--allow-degraded]\n");
}

static void down_usage(void)
{
    printf("Usage:\n");
    printf("  yai down [--ws <id>] [--force]\n");
}

static int kernel_stop_via_rpc(void)
{
    yai_rpc_client_t c;
    if (yai_rpc_connect(&c, "system") != 0) {
        fprintf(stderr, "ERR: cannot connect to root plane\n");
        return -1;
    }

    yai_rpc_set_authority(&c, 1, "operator");

    if (yai_rpc_handshake(&c) != 0) {
        fprintf(stderr, "ERR: handshake failed\n");
        yai_rpc_close(&c);
        return -2;
    }

    const char *payload = "{\"method\":\"stop\",\"params\":{}}";

    char response[YAI_CLI_RPC_RESP_MAX];
    uint32_t resp_len = 0;

    int rc = yai_rpc_call_raw(
        &c,
        (uint32_t)YAI_CMD_CONTROL,
        payload,
        (uint32_t)strlen(payload),
        response,
        sizeof(response) - 1,
        &resp_len
    );

    if (rc == 0) {
        response[resp_len] = '\0';
        /* stop is side-effecty; printing is optional */
        /* printf("%s\n", response); */
    } else {
        fprintf(stderr, "ERR: kernel stop RPC failed (%d)\n", rc);
    }

    yai_rpc_close(&c);
    return rc;
}

/* -----------------------------------------
 * yai up
 * ----------------------------------------- */
int yai_ops_lifecycle_up(int argc, char **argv)
{
    const char *ws = "dev";
    int detach = 0;
    int allow_degraded = 0;

    for (int i = 0; i < argc; i++) {
        const char *a = argv[i];
        if (is_help_arg(a)) {
            up_usage();
            return 0;
        }
        if (!a) continue;

        if ((strcmp(a, "--ws") == 0 || strcmp(a, "--ws-id") == 0 || strcmp(a, "--workspace") == 0) && i + 1 < argc) {
            ws = argv[++i];
            continue;
        }
        if (strcmp(a, "--detach") == 0) { detach = 1; continue; }
        if (strcmp(a, "--allow-degraded") == 0) { allow_degraded = 1; continue; }

        /* ignore old/legacy flags silently */
        if (strcmp(a, "--build") == 0 || strcmp(a, "--ai") == 0 ||
            strcmp(a, "--no-engine") == 0 || strcmp(a, "--no-mind") == 0) {
            continue;
        }
        if (strcmp(a, "--timeout-ms") == 0 && i + 1 < argc) { i++; continue; }

        fprintf(stderr, "ERR: unknown option: %s\n", a);
        up_usage();
        return 2;
    }

    char boot_bin[512];
    char engine_bin[512];

    if (resolve_bin(boot_bin, sizeof(boot_bin), "yai-boot") != 0 ||
        resolve_bin(engine_bin, sizeof(engine_bin), "yai-engine") != 0)
    {
        fprintf(stderr, "[ERROR] Could not resolve runtime binaries.\n");
        return -1;
    }

    if (root_socket_exists() != YAI_OK) {
        char cmd[700];
        snprintf(cmd, sizeof(cmd), "%s >/tmp/yai_cli_boot.log 2>&1 &", boot_bin);
        if (system(cmd) != 0) {
            fprintf(stderr, "[ERROR] Failed to launch Boot.\n");
            return -2;
        }
        if (wait_for_root_ready() != YAI_OK) {
            fprintf(stderr, "[ERROR] Root Plane did not become ready (boot=%s).\n", boot_bin);
            return -3;
        }
    }

    if (wait_for_kernel_ready() != YAI_OK) {
        fprintf(stderr, "[ERROR] Kernel Plane did not become ready (kernel control socket missing).\n");
        return -5;
    }

    char cmd2[1024];
    if (allow_degraded) {
        snprintf(cmd2, sizeof(cmd2),
                 "YAI_ENGINE_ALLOW_DEGRADED=1 %s %s >/tmp/yai_cli_engine.log 2>&1 %s",
                 engine_bin, ws, detach ? "&" : "");
    } else {
        snprintf(cmd2, sizeof(cmd2),
                 "%s %s >/tmp/yai_cli_engine.log 2>&1 %s",
                 engine_bin, ws, detach ? "&" : "");
    }

    if (system(cmd2) != 0) {
        fprintf(stderr, "[ERROR] Failed to launch Engine.\n");
        return -4;
    }

    printf("{\"ok\":true,\"mode\":\"up\",\"ws\":\"%s\"}\n", ws);
    return 0;
}

/* -----------------------------------------
 * yai down
 * ----------------------------------------- */
int yai_ops_lifecycle_down(int argc, char **argv)
{
    int force = 0;

    for (int i = 0; i < argc; i++) {
        const char *a = argv[i];
        if (is_help_arg(a)) { down_usage(); return 0; }
        if (!a) continue;

        if (strcmp(a, "--force") == 0) { force = 1; continue; }
        if ((strcmp(a, "--ws") == 0 || strcmp(a, "--ws-id") == 0 || strcmp(a, "--workspace") == 0) && i + 1 < argc) {
            i++; continue;
        }

        fprintf(stderr, "ERR: unknown option: %s\n", a);
        down_usage();
        return 2;
    }

    if (!force) {
        int rc = kernel_stop_via_rpc();
        if (rc != 0) {
            fprintf(stderr, "ERR: kernel stop failed (%d). Use --force to continue cleanup.\n", rc);
            return rc;
        }
    }

    if (force) {
        system("pkill -f yai-engine >/dev/null 2>&1 || true");
        system("pkill -f yai-root-server >/dev/null 2>&1 || true");
        system("pkill -f yai-kernel >/dev/null 2>&1 || true");
        system("pkill -f yai-boot >/dev/null 2>&1 || true");
    }

    char root_sock[512];
    if (yai_path_root_sock(root_sock, sizeof(root_sock)) == 0) {
        unlink(root_sock);
    }

    const char *home = getenv("HOME");
    if (home && home[0]) {
        char kernel_sock[512];
        char engine_sock[512];
        snprintf(kernel_sock, sizeof(kernel_sock), "%s/.yai/run/kernel/control.sock", home);
        snprintf(engine_sock, sizeof(engine_sock), "%s/.yai/run/engine/control.sock", home);
        unlink(kernel_sock);
        unlink(engine_sock);
    }

    printf("{\"ok\":true,\"mode\":\"down\"}\n");
    return 0;
}

/* -----------------------------------------
 * yai restart  (simple: down --force + up)
 * ----------------------------------------- */
int yai_ops_lifecycle_restart(int argc, char **argv)
{
    (void)argc; (void)argv;
    /* minimal semantics; you can refine later */
    char *down_argv[] = { "--force", NULL };
    (void)yai_ops_lifecycle_down(1, down_argv);

    char *up_argv[] = { NULL };
    return yai_ops_lifecycle_up(0, up_argv);
}