/* SPDX-License-Identifier: Apache-2.0 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*
 * RPC client (strict, low-level)
 *
 * This is the transport-facing client used by ops/handlers.
 * Porcelain should not “do RPC directly” except via ops_dispatch.
 *
 * Contract notes:
 * - ws_id is required for any workspace-scoped operations (L2/L3).
 * - role/arming are part of the envelope authority surface.
 */

typedef struct yai_rpc_client {
    int fd;

    /* workspace id (sanitized by connect) */
    char ws_id[128];

    /* authority */
    uint8_t role;     /* YAI_ROLE_* from roles.h */
    uint8_t arming;   /* 0/1 */
} yai_rpc_client_t;

/* Connect to root control socket, binding this client to ws_id (string copied). */
int  yai_rpc_connect(yai_rpc_client_t *c, const char *ws_id);

/* Close socket if open; safe to call multiple times. */
void yai_rpc_close(yai_rpc_client_t *c);

/* Set authority that will be stamped on subsequent calls. */
void yai_rpc_set_authority(yai_rpc_client_t *c, int arming, const char *role_str);

/*
 * Raw call: send envelope + payload, receive envelope + payload.
 * Returns 0 on success; negative values are transport/protocol errors.
 */
int yai_rpc_call_raw(
    yai_rpc_client_t *c,
    uint32_t command_id,
    const void *payload,
    uint32_t payload_len,
    void *out_buf,
    size_t out_cap,
    uint32_t *out_len);

/*
 * Handshake: validates server readiness and protocol version.
 * Returns 0 on success.
 */
int yai_rpc_handshake(yai_rpc_client_t *c);

/* ------------------------------------------------------------------
 * Optional legacy shim (if you still have call-sites using ctx-style).
 * You can delete this once you migrate all call-sites to yai_rpc_client_t.
 * ------------------------------------------------------------------ */

typedef struct {
    const char *ws;
    const char *socket_path; /* reserved; current implementation resolves via yai_cli/paths.h */
} yai_rpc_ctx_t;

static inline int yai_rpc_init(yai_rpc_ctx_t *ctx, const char *ws)
{
    if (!ctx) return -1;
    ctx->ws = ws;
    ctx->socket_path = 0;
    return 0;
}

#ifdef __cplusplus
}
#endif