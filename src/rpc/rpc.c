#include "yai_cli/rpc/rpc.h"
#include "yai_cli/porcelain/porcelain_errors.h"

#include <string.h>

int yai_rpc_init(yai_rpc_ctx_t* ctx, const char* ws) {
  if (!ctx) return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_GENERIC);
  memset(ctx, 0, sizeof(*ctx));
  ctx->ws = ws;
  ctx->socket_path = NULL; // TODO: resolve via yai_cli paths/env
  return 0;
}

int yai_rpc_ping_root(const yai_rpc_ctx_t* ctx) {
  (void)ctx;
  // TODO: wire to src/runtime/rpc_client.c
  return 0;
}

int yai_rpc_ping_kernel(const yai_rpc_ctx_t* ctx) {
  (void)ctx;
  // TODO: wire to src/runtime/rpc_client.c
  return 0;
}