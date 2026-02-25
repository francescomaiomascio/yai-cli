#define _POSIX_C_SOURCE 200809L

#include <yai_cli/cmd.h>
#include <yai_cli/paths.h>
#include <yai_cli/rpc.h>

#include <yai_protocol_ids.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

typedef struct {
    const char *ws;
    char root_sock[512];
    char kernel_sock[512];
    char engine_sock[512];
    int root_sock_ok;
    int kernel_sock_ok;
    int engine_sock_ok;
    int root_ping_ok;
    int kernel_ping_ok;
    int ready;
} runtime_status_t;

static int path_exists(const char *p)
{
    struct stat st;
    return (p && stat(p, &st) == 0) ? 1 : 0;
}

static int root_ping_ok_impl(void)
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

static int kernel_ping_ok_impl(const yai_cli_opts_t *opt)
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

static runtime_status_t collect_status(const yai_cli_opts_t *opt)
{
    runtime_status_t st;
    memset(&st, 0, sizeof(st));

    st.ws = (opt && opt->ws_id && opt->ws_id[0]) ? opt->ws_id : "dev";

    if (yai_path_root_sock(st.root_sock, sizeof(st.root_sock)) != 0)
        st.root_sock[0] = '\0';
    resolve_kernel_sock(st.kernel_sock, sizeof(st.kernel_sock));
    resolve_engine_sock(st.engine_sock, sizeof(st.engine_sock));

    st.root_sock_ok = path_exists(st.root_sock);
    st.kernel_sock_ok = path_exists(st.kernel_sock);
    st.engine_sock_ok = path_exists(st.engine_sock);

    st.root_ping_ok = root_ping_ok_impl();
    st.kernel_ping_ok = kernel_ping_ok_impl(opt);
    st.ready = st.root_ping_ok && st.kernel_ping_ok;

    return st;
}

static void print_status_human(const runtime_status_t *st)
{
    printf("[status] ws=%s\n", st->ws);
    printf("  root_socket   : %s (%s)\n", st->root_sock_ok ? "ready" : "missing", st->root_sock);
    printf("  kernel_socket : %s (%s)\n", st->kernel_sock_ok ? "ready" : "missing", st->kernel_sock);
    printf("  engine_socket : %s (%s)\n", st->engine_sock_ok ? "ready" : "missing", st->engine_sock);
    printf("  root_ping     : %s\n", st->root_ping_ok ? "ok" : "fail");
    printf("  kernel_ping   : %s\n", st->kernel_ping_ok ? "ok" : "fail");
    printf("  overall       : %s\n", st->ready ? "READY" : "DEGRADED");
}

static void print_status_json(const runtime_status_t *st)
{
    printf("{\"command\":\"status\",\"ok\":%s,\"ws\":\"%s\",\"overall\":\"%s\",\"sockets\":{\"root\":%s,\"kernel\":%s,\"engine\":%s},\"pings\":{\"root\":%s,\"kernel\":%s},\"paths\":{\"root\":\"%s\",\"kernel\":\"%s\",\"engine\":\"%s\"}}\n",
           st->ready ? "true" : "false",
           st->ws,
           st->ready ? "READY" : "DEGRADED",
           st->root_sock_ok ? "true" : "false",
           st->kernel_sock_ok ? "true" : "false",
           st->engine_sock_ok ? "true" : "false",
           st->root_ping_ok ? "true" : "false",
           st->kernel_ping_ok ? "true" : "false",
           st->root_sock,
           st->kernel_sock,
           st->engine_sock);
}

static void print_doctor_json(const runtime_status_t *st)
{
    printf("{\"command\":\"doctor\",\"doctor\":\"%s\",\"ok\":%s,\"ws\":\"%s\",\"overall\":\"%s\",\"hint\":\"use yai up --ws <id> --detach --allow-degraded; then yai root ping && yai kernel --arming --role operator ping\",\"status\":{\"ok\":%s,\"overall\":\"%s\",\"sockets\":{\"root\":%s,\"kernel\":%s,\"engine\":%s},\"pings\":{\"root\":%s,\"kernel\":%s},\"paths\":{\"root\":\"%s\",\"kernel\":\"%s\",\"engine\":\"%s\"}}}\n",
           st->ready ? "ok" : "needs_attention",
           st->ready ? "true" : "false",
           st->ws,
           st->ready ? "READY" : "DEGRADED",
           st->ready ? "true" : "false",
           st->ready ? "READY" : "DEGRADED",
           st->root_sock_ok ? "true" : "false",
           st->kernel_sock_ok ? "true" : "false",
           st->engine_sock_ok ? "true" : "false",
           st->root_ping_ok ? "true" : "false",
           st->kernel_ping_ok ? "true" : "false",
           st->root_sock,
           st->kernel_sock,
           st->engine_sock);
}

int yai_cmd_status(int argc, char **argv, const yai_cli_opts_t *opt)
{
    (void)argv;
    if (argc > 0) {
        fprintf(stderr, "Usage: yai status [--ws <id>] [--json] [--arming] [--role <role>]\n");
        return 2;
    }

    runtime_status_t st = collect_status(opt);

    if (opt && opt->json)
        print_status_json(&st);
    else
        print_status_human(&st);

    return st.ready ? 0 : 1;
}

int yai_cmd_doctor(int argc, char **argv, const yai_cli_opts_t *opt)
{
    (void)argv;
    if (argc > 0) {
        fprintf(stderr, "Usage: yai doctor [--ws <id>] [--json]\n");
        return 2;
    }

    runtime_status_t st = collect_status(opt);

    if (opt && opt->json) {
        print_doctor_json(&st);
    } else {
        if (st.ready) {
            printf("[doctor] OK: runtime is healthy (ws=%s)\n", st.ws);
        } else {
            printf("[doctor] ATTENTION: runtime not ready (ws=%s, overall=%s)\n", st.ws, st.ready ? "READY" : "DEGRADED");
            printf("[doctor] root_ping=%s kernel_ping=%s root_sock=%s kernel_sock=%s\n",
                   st.root_ping_ok ? "ok" : "fail",
                   st.kernel_ping_ok ? "ok" : "fail",
                   st.root_sock_ok ? "ready" : "missing",
                   st.kernel_sock_ok ? "ready" : "missing");
            printf("[doctor] Try:\n");
            printf("  yai down --ws dev --force || true\n");
            printf("  yai up --ws dev --detach --allow-degraded\n");
            printf("  yai root ping\n");
            printf("  yai kernel --arming --role operator ping\n");
        }
    }

    return st.ready ? 0 : 1;
}
