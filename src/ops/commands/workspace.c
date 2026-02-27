/* SPDX-License-Identifier: Apache-2.0 */
// src/ops/commands/workspace.c

#define _POSIX_C_SOURCE 200809L

#include <yai_cli/ops/ops.h>
#include <yai_cli/fmt.h>
#include <yai_cli/rpc/rpc.h>

#include <yai_protocol_ids.h>

#include <stdio.h>
#include <string.h>
#include <stdint.h>

enum { YAI_CLI_RPC_RESP_MAX = 4096 };

static void ws_usage(void) {
    fprintf(stderr,
        "Workspace Management (L1 - Root Plane)\n"
        "Usage:\n"
        "  yai ws list\n"
        "  yai ws create  <id>\n"
        "  yai ws destroy <id>\n");
}

int yai_ops_control_workspace(int argc, char **argv)
{
    if (argc < 1) {
        ws_usage();
        return 1;
    }

    const char *sub = argv[0];

    yai_rpc_client_t client;
    if (yai_rpc_connect(&client, "system") != 0) {
        fprintf(stderr, "ERR: cannot connect to root plane\n");
        return 2;
    }

    /* TODO: bind arming/role/json when ops ctx exists */
    yai_rpc_set_authority(&client, 1, "operator");

    if (yai_rpc_handshake(&client) != 0) {
        fprintf(stderr, "ERR: handshake failed\n");
        yai_rpc_close(&client);
        return 3;
    }

    char payload[512];

    if (strcmp(sub, "list") == 0) {
        snprintf(payload, sizeof(payload),
                 "{\"method\":\"ws_list\",\"params\":{}}");
    } else if (strcmp(sub, "create") == 0 || strcmp(sub, "destroy") == 0) {
        if (argc < 2 || !argv[1] || !argv[1][0]) {
            ws_usage();
            yai_rpc_close(&client);
            return 4;
        }

        const char *method = (strcmp(sub, "create") == 0) ? "ws_create" : "ws_destroy";
        snprintf(payload, sizeof(payload),
                 "{\"method\":\"%s\",\"params\":{\"ws_id\":\"%s\"}}",
                 method, argv[1]);
    } else if (strcmp(sub, "help") == 0 || strcmp(sub, "--help") == 0 || strcmp(sub, "-h") == 0) {
        ws_usage();
        yai_rpc_close(&client);
        return 0;
    } else {
        ws_usage();
        yai_rpc_close(&client);
        return 4;
    }

    char response[YAI_CLI_RPC_RESP_MAX];
    uint32_t resp_len = 0;

    int rc = yai_rpc_call_raw(
        &client,
        (uint32_t)YAI_CMD_CONTROL,
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
        fprintf(stderr, "ERR: ws command failed (%d)\n", rc);
    }

    yai_rpc_close(&client);
    return rc;
}