// src/ops/ops_dispatch.c
#include "yai_cli/ops/ops_dispatch.h"
#include "yai_cli/ops/ops_dispatch_gen.h"
#include "yai_cli/porcelain/porcelain_errors.h"

#include <string.h>

int yai_ops_dispatch_by_id(const char* command_id, int argc, char** argv) {
  if (!command_id || command_id[0] == '\0') {
    yai_porcelain_err_print(YAI_PORCELAIN_ERR_USAGE, "missing command id");
    return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_USAGE);
  }

  // Registry-driven: at the moment there are no hardcoded handlers.
  // This will be replaced by the generic executor (option 2).
  if (!kOpsMap || kOpsMapLen == 0) {
    yai_porcelain_err_print(
      YAI_PORCELAIN_ERR_USAGE,
      "command id not mapped to an ops handler yet (registry-driven mode: executor not installed)"
    );
    return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_USAGE);
  }

  for (size_t i = 0; i < kOpsMapLen; i++) {
    if (kOpsMap[i].id && strcmp(kOpsMap[i].id, command_id) == 0) {
      return kOpsMap[i].fn(argc, argv);
    }
  }

  yai_porcelain_err_print(
    YAI_PORCELAIN_ERR_USAGE,
    "command id not mapped to an ops handler yet"
  );
  return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_USAGE);
}