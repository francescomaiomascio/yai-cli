// src/porcelain/porcelain_errors.c
#include "yai_cli/porcelain/porcelain_errors.h"

#include <stdio.h>

const char* yai_porcelain_err_name(yai_porcelain_err_t e) {
  switch (e) {
    case YAI_PORCELAIN_ERR_OK: return "success";
    case YAI_PORCELAIN_ERR_GENERIC: return "generic_failure";
    case YAI_PORCELAIN_ERR_USAGE: return "invalid_arguments_or_contract_violation";
    case YAI_PORCELAIN_ERR_DEP_MISSING: return "dependency_missing";
    case YAI_PORCELAIN_ERR_RUNTIME_NOT_READY: return "runtime_not_ready";
    default: return "unknown";
  }
}

int yai_porcelain_err_exit_code(yai_porcelain_err_t e) {
  // Matches your commands.v1.json exit_codes map
  switch (e) {
    case YAI_PORCELAIN_ERR_OK: return 0;
    case YAI_PORCELAIN_ERR_GENERIC: return 1;
    case YAI_PORCELAIN_ERR_USAGE: return 2;
    case YAI_PORCELAIN_ERR_DEP_MISSING: return 3;
    case YAI_PORCELAIN_ERR_RUNTIME_NOT_READY: return 4;
    default: return 1;
  }
}

void yai_porcelain_err_print(yai_porcelain_err_t e, const char* msg) {
  if (!msg) msg = "error";
  fprintf(stderr, "yai: %s: %s\n", yai_porcelain_err_name(e), msg);
}