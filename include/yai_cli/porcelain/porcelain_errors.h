// include/yai_cli/porcelain/porcelain_errors.h
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum yai_porcelain_err_e {
  YAI_PORCELAIN_ERR_OK = 0,

  // CLI usage / arguments
  YAI_PORCELAIN_ERR_USAGE = 2,

  // Dependency missing (law registry not readable, etc.)
  YAI_PORCELAIN_ERR_DEP_MISSING = 3,

  // Runtime not ready
  YAI_PORCELAIN_ERR_RUNTIME_NOT_READY = 4,

  // Generic failure
  YAI_PORCELAIN_ERR_GENERIC = 1
} yai_porcelain_err_t;

const char* yai_porcelain_err_name(yai_porcelain_err_t e);
int yai_porcelain_err_exit_code(yai_porcelain_err_t e);

// Render a user-facing error line (stderr).
void yai_porcelain_err_print(yai_porcelain_err_t e, const char* msg);

#ifdef __cplusplus
}
#endif