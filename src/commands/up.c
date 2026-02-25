#include <yai_cli/cli.h>
#include <yai_cli/cmd.h>
#include <yai_cli/paths.h>

#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define YAI_OK 0
#define WAIT_RETRIES 20
#define WAIT_INTERVAL_US 200000

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

static int run_kernel_stop(const yai_cli_opts_t *opt)
{
    char *argv_stop[] = {"stop"};
    return yai_cmd_kernel(1, argv_stop, opt);
}

static int is_help_arg(const char *a)
{
    return a && (strcmp(a, "-h") == 0 || strcmp(a, "--help") == 0 || strcmp(a, "help") == 0);
}

static void up_usage(void)
{
    printf("Usage:\n");
    printf("  yai up [--ws <id>] [--ws-id <id>] [--workspace <id>] [--detach] [--allow-degraded]\n");
}

static void down_usage(void)
{
    printf("Usage:\n");
    printf("  yai down [--ws <id>] [--ws-id <id>] [--workspace <id>] [--force]\n");
}

int yai_cmd_up(int argc, char **argv, const yai_cli_opts_t *opt)
{
    const char *ws = (opt && opt->ws_id && opt->ws_id[0]) ? opt->ws_id : "dev";
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
        if (strcmp(a, "--detach") == 0) {
            detach = 1;
            continue;
        }
        if (strcmp(a, "--allow-degraded") == 0) {
            allow_degraded = 1;
            continue;
        }
        if (strcmp(a, "--build") == 0 || strcmp(a, "--ai") == 0 || strcmp(a, "--no-engine") == 0 || strcmp(a, "--no-mind") == 0) {
            continue;
        }
        if (strcmp(a, "--timeout-ms") == 0 && i + 1 < argc) {
            i++;
            continue;
        }
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

    char cmd2[1024];
    if (allow_degraded) {
        snprintf(cmd2, sizeof(cmd2), "YAI_ENGINE_ALLOW_DEGRADED=1 %s %s >/tmp/yai_cli_engine.log 2>&1 %s", engine_bin, ws, detach ? "&" : "");
    } else {
        snprintf(cmd2, sizeof(cmd2), "%s %s >/tmp/yai_cli_engine.log 2>&1 %s", engine_bin, ws, detach ? "&" : "");
    }

    if (system(cmd2) != 0) {
        fprintf(stderr, "[ERROR] Failed to launch Engine.\n");
        return -4;
    }

    printf("{\"ok\":true,\"mode\":\"up\",\"ws\":\"%s\"}\n", ws);
    return 0;
}

int yai_cmd_down(int argc, char **argv, const yai_cli_opts_t *opt)
{
    (void)opt;
    int force = 0;

    for (int i = 0; i < argc; i++) {
        const char *a = argv[i];
        if (is_help_arg(a)) {
            down_usage();
            return 0;
        }
        if (!a) continue;
        if (strcmp(a, "--force") == 0) {
            force = 1;
            continue;
        }
        if ((strcmp(a, "--ws") == 0 || strcmp(a, "--ws-id") == 0 || strcmp(a, "--workspace") == 0) && i + 1 < argc) {
            i++;
            continue;
        }
        fprintf(stderr, "ERR: unknown option: %s\n", a);
        down_usage();
        return 2;
    }

    yai_cli_opts_t stop_opt = {0};
    stop_opt.arming = 1;
    stop_opt.role = "operator";
    stop_opt.client_version = "yai-cli/1.0";

    int rc = run_kernel_stop(&stop_opt);
    if (rc != 0 && !force) {
        fprintf(stderr, "ERR: kernel stop failed (%d). Use --force to continue cleanup.\n", rc);
        return rc;
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
