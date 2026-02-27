/* SPDX-License-Identifier: Apache-2.0 */
// src/ops/commands/kernel.c

#define _POSIX_C_SOURCE 200809L

#include <yai_cli/ops/ops.h>
#include <yai_cli/fmt.h>
#include <yai_cli/rpc/rpc.h>

#include <yai_protocol_ids.h>

#include <stdio.h>
#include <string.h>
#include <stdint.h>

enum { YAI_CLI_RPC_RESP_MAX = 4096 };

static void usage_kernel(void)
{
    fprintf(stderr, "Usage: yai kernel <command>\n");
}

static int connect_root_plane(yai_rpc_client_t *client)
{
    if (!client) return -1;
    memset(client, 0, sizeof(*client));

    /* CRITICAL: root plane ws_id is "system" */
    if (yai_rpc_connect(client, "system") != 0) {
        fprintf(stderr, "ERR: cannot connect to root plane\n");
        return -2;
    }

    /* TODO: bind to porcelain ctx once ops ctx exists */
    yai_rpc_set_authority(client, 1, "operator");

    if (yai_rpc_handshake(client) != 0) {
        fprintf(stderr, "ERR: handshake failed\n");
        yai_rpc_close(client);
        return -3;
    }

    return 0;
}

int yai_ops_control_kernel(int argc, char **argv)
{
    if (argc < 1) {
        usage_kernel();
        return 1;
    }

    const char *cmd = argv[0];

    /* keep current behavior: ping uses PING, everything else CONTROL */
    uint32_t command_id =
        (strcmp(cmd, "ping") == 0)
        ? (uint32_t)YAI_CMD_PING
        : (uint32_t)YAI_CMD_CONTROL;

    yai_rpc_client_t client;
    int rc = connect_root_plane(&client);
    if (rc != 0) return rc;

    char payload[256];
    int n = snprintf(
        payload,
        sizeof(payload),
        "{\"method\":\"%s\",\"params\":{}}",
        cmd
    );

    if (n <= 0 || (size_t)n >= sizeof(payload)) {
        fprintf(stderr, "ERR: payload build failed\n");
        yai_rpc_close(&client);
        return -4;
    }

    char response[YAI_CLI_RPC_RESP_MAX];
    uint32_t resp_len = 0;

    rc = yai_rpc_call_raw(
        &client,
        command_id,
        payload,
        (uint32_t)strlen(payload),
        response,
        sizeof(response) - 1,
        &resp_len
    );

    if (rc == 0) {
        response[resp_len] = '\0';
        yai_print_response(response, 0);
    } else {
        fprintf(stderr, "ERR: kernel command failed (%d)\n", rc);
    }

    yai_rpc_close(&client);
    return rc;
}