/* SPDX-License-Identifier: Apache-2.0 */
// src/ops/commands/status.c

#define _POSIX_C_SOURCE 200809L

#include <yai_cli/ops/ops.h>
#include <yai_cli/paths.h>
#include <yai_cli/rpc/rpc.h>

#include <yai_protocol_ids.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdint.h>

enum { YAI_CLI_RPC_RESP_MAX = 4096 };

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
    int engine_rpc_ok;
    int ready;
} runtime_status_t;

static int path_exists(const char *p)
{
    struct stat st;
    return (p && stat(p, &st) == 0) ? 1 : 0;
}

static void resolve_kernel_sock(char *out, size_t cap)
{
    const char *home = getenv("HOME");
    if (!home || !home[0]) { out[0] = '\0'; return; }
    snprintf(out, cap, "%s/.yai/run/kernel/control.sock", home);
}

static void resolve_engine_sock(char *out, size_t cap)
{
    const char *home = getenv("HOME");
    if (!home || !home[0]) { out[0] = '\0'; return; }
    snprintf(out, cap, "%s/.yai/run/engine/control.sock", home);
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

    char response[YAI_CLI_RPC_RESP_MAX];
    uint32_t resp_len = 0;

    int rc = yai_rpc_call_raw(
        &c,
        (uint32_t)YAI_CMD_PING,
        NULL,
        0,
        response,
        sizeof(response) - 1,
        &resp_len
    );

    yai_rpc_close(&c);
    return rc == 0;
}

static int kernel_ping_ok_impl(void)
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

    const char payload[] = "{\"method\":\"ping\",\"params\":{}}";

    char response[YAI_CLI_RPC_RESP_MAX];
    uint32_t resp_len = 0;

    int rc = yai_rpc_call_raw(
        &c,
        (uint32_t)YAI_CMD_PING,
        payload,
        (uint32_t)strlen(payload),
        response,
        sizeof(response) - 1,
        &resp_len
    );

    yai_rpc_close(&c);
    return rc == 0;
}

static int engine_rpc_ok_impl(const char *ws)
{
    if (!ws || !ws[0]) return 0;

    yai_rpc_client_t c;
    memset(&c, 0, sizeof(c));

    if (yai_rpc_connect(&c, ws) != 0)
        return 0;

    yai_rpc_set_authority(&c, 1, "operator");

    if (yai_rpc_handshake(&c) != 0) {
        yai_rpc_close(&c);
        return 0;
    }

    const char payload[] = "{\"method\":\"get_node\",\"params\":{\"id\":\"__yai_status_probe__\"}}";

    char response[YAI_CLI_RPC_RESP_MAX];
    uint32_t resp_len = 0;

    int rc = yai_rpc_call_raw(
        &c,
        (uint32_t)YAI_CMD_STORAGE_RPC,
        payload,
        (uint32_t)strlen(payload),
        response,
        sizeof(response) - 1,
        &resp_len
    );

    yai_rpc_close(&c);
    return rc == 0;
}

static runtime_status_t collect_status(const char *ws)
{
    runtime_status_t st;
    memset(&st, 0, sizeof(st));

    st.ws = (ws && ws[0]) ? ws : "dev";

    if (yai_path_root_sock(st.root_sock, sizeof(st.root_sock)) != 0)
        st.root_sock[0] = '\0';
    resolve_kernel_sock(st.kernel_sock, sizeof(st.kernel_sock));
    resolve_engine_sock(st.engine_sock, sizeof(st.engine_sock));

    st.root_sock_ok   = path_exists(st.root_sock);
    st.kernel_sock_ok = path_exists(st.kernel_sock);
    st.engine_sock_ok = path_exists(st.engine_sock);

    st.root_ping_ok   = root_ping_ok_impl();
    st.kernel_ping_ok = kernel_ping_ok_impl();
    st.engine_rpc_ok  = engine_rpc_ok_impl(st.ws);

    st.ready = st.root_ping_ok && st.kernel_ping_ok && st.engine_rpc_ok;
    return st;
}

static void print_status_human(const runtime_status_t *st)
{
    printf("[status] ws=%s\n", st->ws);
    printf("  root_socket   : %s (%s)\n", st->root_sock_ok ? "ready" : "missing", st->root_sock);
    printf("  kernel_socket : %s (%s)\n", st->kernel_sock_ok ? "ready" : "missing", st->kernel_sock);
    printf("  engine_socket : %s (%s) [informational]\n", st->engine_sock_ok ? "ready" : "missing", st->engine_sock);
    printf("  root_ping     : %s\n", st->root_ping_ok ? "ok" : "fail");
    printf("  kernel_ping   : %s\n", st->kernel_ping_ok ? "ok" : "fail");
    printf("  engine_rpc    : %s\n", st->engine_rpc_ok ? "ok" : "fail");
    printf("  overall       : %s\n", st->ready ? "READY" : "DEGRADED");
}

static const char* parse_ws_flag(int argc, char **argv)
{
    for (int i = 0; i < argc; i++) {
        if (!argv[i]) continue;
        if ((strcmp(argv[i], "--ws") == 0 || strcmp(argv[i], "--ws-id") == 0 || strcmp(argv[i], "--workspace") == 0) && (i + 1 < argc)) {
            return argv[i + 1];
        }
    }
    return NULL;
}

int yai_ops_inspect_status(int argc, char **argv)
{
    /* supports: yai status [--ws <id>] */
    const char *ws = parse_ws_flag(argc, argv);

    /* reject extra positional args (keep strict) */
    for (int i = 0; i < argc; i++) {
        const char *a = argv[i];
        if (!a) continue;
        if (strcmp(a, "--ws") == 0 || strcmp(a, "--ws-id") == 0 || strcmp(a, "--workspace") == 0) { i++; continue; }
        fprintf(stderr, "Usage: yai status [--ws <id>]\n");
        return 2;
    }

    runtime_status_t st = collect_status(ws);
    print_status_human(&st);

    return st.ready ? 0 : 1;
}

/* The other inspect handlers are not implemented yet (logs/monitor/events).
 * Keep them as stubs so the linker is happy if mapped later.
 */
int yai_ops_inspect_logs(int argc, char **argv)    { (void)argc; (void)argv; fprintf(stderr, "ERR: not implemented\n"); return 2; }
int yai_ops_inspect_monitor(int argc, char **argv) { (void)argc; (void)argv; fprintf(stderr, "ERR: not implemented\n"); return 2; }
int yai_ops_inspect_events(int argc, char **argv)  { (void)argc; (void)argv; fprintf(stderr, "ERR: not implemented\n"); return 2; }