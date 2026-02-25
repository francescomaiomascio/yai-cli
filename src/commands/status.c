#define _POSIX_C_SOURCE 200809L

#include <yai_cli/cmd.h>
#include <yai_cli/paths.h>
#include <yai_cli/rpc.h>

#include <yai_protocol_ids.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

static int path_exists(const char *p)
{
    struct stat st;
    return (p && stat(p, &st) == 0) ? 1 : 0;
}

static int root_ping_ok(void)
{
    yai_rpc_client_t c;
    memset(&c, 0, sizeof(c));

    if (yai_rpc_connect(&c, "system") != 0)
        return 0;

    yai_rpc_set_authority(&c, 1, "operator");
    if (yai_rpc_handshake(&c) != 0) {
        yai_rpc_close(&c);
        return 0;
    }

    char response[YAI_RPC_LINE_MAX];
    uint32_t resp_len = 0;
    int rc = yai_rpc_call_raw(
        &c,
        YAI_CMD_PING,
        NULL,
        0,
        response,
        sizeof(response) - 1,
        &resp_len);

    yai_rpc_close(&c);
    return rc == 0;
}

static int kernel_ping_ok(const yai_cli_opts_t *opt)
{
    yai_rpc_client_t c;
    memset(&c, 0, sizeof(c));

    if (yai_rpc_connect(&c, "system") != 0)
        return 0;

    const char *role = (opt && opt->role && opt->role[0]) ? opt->role : "operator";
    int arming = (opt && opt->arming) ? opt->arming : 1;
    yai_rpc_set_authority(&c, arming, role);

    if (yai_rpc_handshake(&c) != 0) {
        yai_rpc_close(&c);
        return 0;
    }

    const char payload[] = "{\"method\":\"ping\",\"params\":{}}";
    char response[YAI_RPC_LINE_MAX];
    uint32_t resp_len = 0;

    int rc = yai_rpc_call_raw(
        &c,
        YAI_CMD_PING,
        payload,
        (uint32_t)strlen(payload),
        response,
        sizeof(response) - 1,
        &resp_len);

    yai_rpc_close(&c);
    return rc == 0;
}

static void resolve_kernel_sock(char *out, size_t cap)
{
    const char *home = getenv("HOME");
    if (!home || !home[0]) {
        out[0] = '\0';
        return;
    }
    snprintf(out, cap, "%s/.yai/run/kernel/control.sock", home);
}

static void resolve_engine_sock(char *out, size_t cap)
{
    const char *home = getenv("HOME");
    if (!home || !home[0]) {
        out[0] = '\0';
        return;
    }
    snprintf(out, cap, "%s/.yai/run/engine/control.sock", home);
}

int yai_cmd_status(int argc, char **argv, const yai_cli_opts_t *opt)
{
    (void)argv;
    if (argc > 0) {
        fprintf(stderr, "Usage: yai status [--ws <id>] [--json] [--arming] [--role <role>]\n");
        return 2;
    }

    const char *ws = (opt && opt->ws_id && opt->ws_id[0]) ? opt->ws_id : "dev";

    char root_sock[512] = {0};
    char kernel_sock[512] = {0};
    char engine_sock[512] = {0};

    if (yai_path_root_sock(root_sock, sizeof(root_sock)) != 0)
        root_sock[0] = '\0';
    resolve_kernel_sock(kernel_sock, sizeof(kernel_sock));
    resolve_engine_sock(engine_sock, sizeof(engine_sock));

    int root_sock_ok = path_exists(root_sock);
    int kernel_sock_ok = path_exists(kernel_sock);
    int engine_sock_ok = path_exists(engine_sock);

    int root_ping = root_ping_ok();
    int kernel_ping = kernel_ping_ok(opt);

    int ok = root_ping && kernel_ping;

    if (opt && opt->json) {
        printf("{\"ok\":%s,\"ws\":\"%s\",\"sockets\":{\"root\":%s,\"kernel\":%s,\"engine\":%s},\"pings\":{\"root\":%s,\"kernel\":%s},\"paths\":{\"root\":\"%s\",\"kernel\":\"%s\",\"engine\":\"%s\"}}\n",
               ok ? "true" : "false",
               ws,
               root_sock_ok ? "true" : "false",
               kernel_sock_ok ? "true" : "false",
               engine_sock_ok ? "true" : "false",
               root_ping ? "true" : "false",
               kernel_ping ? "true" : "false",
               root_sock,
               kernel_sock,
               engine_sock);
    } else {
        printf("[status] ws=%s\n", ws);
        printf("  root_socket   : %s (%s)\n", root_sock_ok ? "ready" : "missing", root_sock);
        printf("  kernel_socket : %s (%s)\n", kernel_sock_ok ? "ready" : "missing", kernel_sock);
        printf("  engine_socket : %s (%s)\n", engine_sock_ok ? "ready" : "missing", engine_sock);
        printf("  root_ping     : %s\n", root_ping ? "ok" : "fail");
        printf("  kernel_ping   : %s\n", kernel_ping ? "ok" : "fail");
        printf("  overall       : %s\n", ok ? "READY" : "DEGRADED");
    }

    return ok ? 0 : 1;
}

int yai_cmd_doctor(int argc, char **argv, const yai_cli_opts_t *opt)
{
    (void)argv;
    if (argc > 0) {
        fprintf(stderr, "Usage: yai doctor [--ws <id>] [--json]\n");
        return 2;
    }

    int rc = yai_cmd_status(0, NULL, opt);

    if (opt && opt->json) {
        printf("{\"doctor\":%s,\"hint\":\"use yai up --ws <id> --detach --allow-degraded; then yai root ping && yai kernel --arming --role operator ping\"}\n",
               (rc == 0) ? "\"ok\"" : "\"needs_attention\"");
    } else {
        if (rc == 0) {
            printf("[doctor] OK: runtime is healthy\n");
        } else {
            printf("[doctor] ATTENTION: runtime not ready\n");
            printf("[doctor] Try:\n");
            printf("  yai down --ws dev --force || true\n");
            printf("  yai up --ws dev --detach --allow-degraded\n");
            printf("  yai root ping\n");
            printf("  yai kernel --arming --role operator ping\n");
        }
    }

    return rc;
}
