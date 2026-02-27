/* SPDX-License-Identifier: Apache-2.0 */
#define _POSIX_C_SOURCE 200809L

#include <yai_cli/ops/ops.h>
#include <yai_cli/rpc/rpc.h>

#include <yai_protocol_ids.h>

#include <stdio.h>
#include <string.h>
#include <stdint.h>

static void usage_root(void)
{
    fprintf(stderr,
        "Machine Root Plane\n"
        "Usage:\n"
        "  yai root ping\n"
        "  yai root status\n");
}

static int root_connect_and_handshake(yai_rpc_client_t *c)
{
    if (!c) return -1;
    memset(c, 0, sizeof(*c));

    /* Root plane is global: fixed workspace "system" */
    if (yai_rpc_connect(c, "system") != 0) {
        fprintf(stderr, "[CLI] Failed to connect to root plane\n");
        return -2;
    }

    /* TODO: bind this to porcelain ctx (arming/role) when ops ctx exists */
    yai_rpc_set_authority(c, 1, "operator");

    int rc = yai_rpc_handshake(c);
    if (rc != 0) {
        fprintf(stderr, "[CLI] Root handshake failed (rc=%d)\n", rc);
        yai_rpc_close(c);
        return -3;
    }

    return 0;
}

static int root_ping(void)
{
    yai_rpc_client_t c;
    if (root_connect_and_handshake(&c) != 0)
        return 3;

    char response[YAI_RPC_LINE_MAX];
    uint32_t resp_len = 0;

    int rc = yai_rpc_call_raw(
        &c,
        YAI_CMD_PING,
        NULL,
        0,
        response,
        sizeof(response) - 1,
        &resp_len
    );

    if (rc != 0) {
        fprintf(stderr, "[CLI] Root ping failed (rc=%d)\n", rc);
        yai_rpc_close(&c);
        return 4;
    }

    response[resp_len] = '\0';
    puts(response);

    yai_rpc_close(&c);
    return 0;
}

/* ============================================================
   OPS ENTRYPOINT (new world)
   ============================================================ */

int yai_ops_control_root(int argc, char **argv)
{
    const char *sub = (argc >= 1) ? argv[0] : NULL;

    if (!sub || !sub[0] || strcmp(sub, "help") == 0) {
        usage_root();
        return sub ? 0 : 2;
    }

    if (strcmp(sub, "ping") == 0)
        return root_ping();

    if (strcmp(sub, "status") == 0)
        return root_ping();

    fprintf(stderr, "ERR: unknown root subcommand: %s\n", sub);
    usage_root();
    return 2;
}