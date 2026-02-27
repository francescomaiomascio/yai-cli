/* SPDX-License-Identifier: Apache-2.0 */
// src/ops/commands/engine.c
//
// Implements yai.control.providers (workspace-plane gates):
//   yai engine --ws <id> <storage|provider|embedding> <method> [params_json]
//
// NOTE: we keep the file name for now, but the exported symbol is the
// mapped ops handler: yai_ops_control_providers().

#define _POSIX_C_SOURCE 200809L

#include <yai_cli/ops/ops.h>
#include <yai_cli/fmt.h>
#include <yai_cli/rpc/rpc.h>

#include <yai_protocol_ids.h>

#include <stdio.h>
#include <string.h>
#include <stdint.h>

enum { YAI_CLI_RPC_RESP_MAX = 4096 };
enum { YAI_CLI_PAYLOAD_MAX  = 8192 };

static void usage_engine(void)
{
    fprintf(stderr,
        "Engine Gates (L2)\n"
        "Usage:\n"
        "  yai engine --ws <id> <storage|provider|embedding> <method> [params_json]\n");
}

/* minimal parsing: find --ws <id>, remove it in-place */
static int parse_ws_and_shift(int argc, char **argv, const char **out_ws)
{
    if (!out_ws) return 1;
    *out_ws = NULL;

    for (int i = 0; i < argc; i++) {
        if (!argv[i]) continue;
        if (strcmp(argv[i], "--ws") == 0) {
            if (i + 1 >= argc || !argv[i + 1] || !argv[i + 1][0]) return 2;
            *out_ws = argv[i + 1];

            /* shift left by 2 */
            for (int j = i; j + 2 < argc; j++) {
                argv[j] = argv[j + 2];
            }
            argc -= 2;
            if (argc >= 0) argv[argc] = NULL;
            if (argc + 1 >= 0) argv[argc + 1] = NULL;

            return 0;
        }
    }

    return 0;
}

static uint32_t gate_to_command_id(const char *gate)
{
    if (!gate) return 0;
    if (strcmp(gate, "storage") == 0)   return (uint32_t)YAI_CMD_STORAGE_RPC;
    if (strcmp(gate, "provider") == 0)  return (uint32_t)YAI_CMD_PROVIDER_RPC;
    if (strcmp(gate, "embedding") == 0) return (uint32_t)YAI_CMD_EMBEDDING_RPC;
    return 0;
}

/* mapped handler: yai.control.providers */
int yai_ops_control_providers(int argc, char **argv)
{
    if (argc < 1) {
        usage_engine();
        return 1;
    }

    const char *ws = NULL;
    int prc = parse_ws_and_shift(argc, argv, &ws);
    if (prc != 0) {
        fprintf(stderr, "ERR: invalid --ws usage\n");
        usage_engine();
        return 2;
    }

    if (!ws || !ws[0]) {
        fprintf(stderr, "FATAL: engine requires --ws <id>\n");
        return 2;
    }

    /* after stripping --ws <id> we expect:
       <gate> <method> [params_json] */
    if (argc < 2) {
        usage_engine();
        return 1;
    }

    const char *gate   = argv[0];
    const char *method = argv[1];
    const char *params =
        (argc > 2 && argv[2] && argv[2][0]) ? argv[2] : "{}";

    uint32_t command_id = gate_to_command_id(gate);
    if (command_id == 0) {
        fprintf(stderr, "ERR: invalid gate (expected storage|provider|embedding)\n");
        return 3;
    }

    yai_rpc_client_t client;
    if (yai_rpc_connect(&client, ws) != 0) {
        fprintf(stderr, "ERR: cannot connect to workspace plane (ws=%s)\n", ws);
        return 4;
    }

    /* TODO: bind arming/role/json to porcelain ctx once ops ctx exists */
    yai_rpc_set_authority(&client, 1, "operator");

    if (yai_rpc_handshake(&client) != 0) {
        fprintf(stderr, "ERR: handshake failed\n");
        yai_rpc_close(&client);
        return 5;
    }

    char payload[YAI_CLI_PAYLOAD_MAX];
    int n = snprintf(payload, sizeof(payload),
                     "{\"method\":\"%s\",\"params\":%s}",
                     method, params);

    if (n <= 0 || (size_t)n >= sizeof(payload)) {
        fprintf(stderr, "ERR: payload build failed\n");
        yai_rpc_close(&client);
        return 6;
    }

    char response[YAI_CLI_RPC_RESP_MAX];
    uint32_t resp_len = 0;

    int rc = yai_rpc_call_raw(
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
        fprintf(stderr, "ERR: engine RPC failed (%d)\n", rc);
    }

    yai_rpc_close(&client);
    return rc;
}