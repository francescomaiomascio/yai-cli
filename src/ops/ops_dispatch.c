#include "yai_cli/ops/ops_dispatch.h"
#include "yai_cli/ops/ops.h"
#include "yai_cli/porcelain/porcelain_errors.h"

#include <string.h>

typedef struct {
  const char* id;
  int (*fn)(int, char**);
} yai_ops_map_t;

static const yai_ops_map_t kOpsMap[] = {
  // lifecycle
  {"yai.lifecycle.up",       yai_ops_lifecycle_up},
  {"yai.lifecycle.restart",  yai_ops_lifecycle_restart},
  {"yai.lifecycle.down",     yai_ops_lifecycle_down},

  // inspect
  {"yai.inspect.status",     yai_ops_inspect_status},
  {"yai.inspect.logs",       yai_ops_inspect_logs},
  {"yai.inspect.monitor",    yai_ops_inspect_monitor},
  {"yai.inspect.events",     yai_ops_inspect_events},

  // verify
  {"yai.verify.verify",      yai_ops_verify_verify},
  {"yai.verify.test",        yai_ops_verify_test},

  // control
  {"yai.control.root",       yai_ops_control_root},
  {"yai.control.kernel",     yai_ops_control_kernel},
  {"yai.control.sessions",   yai_ops_control_sessions},
  {"yai.control.providers",  yai_ops_control_providers},
  {"yai.control.chat",       yai_ops_control_chat},
  {"yai.control.shell",      yai_ops_control_shell},
  {"yai.control.dsar",       yai_ops_control_dsar},
  {"yai.control.workspace",  yai_ops_control_workspace},

};

int yai_ops_dispatch_by_id(const char* command_id, int argc, char** argv) {
  if (!command_id || command_id[0] == '\0') {
    yai_porcelain_err_print(YAI_PORCELAIN_ERR_USAGE, "missing command id");
    return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_USAGE);
  }

  for (unsigned i = 0; i < (sizeof(kOpsMap) / sizeof(kOpsMap[0])); i++) {
    if (strcmp(kOpsMap[i].id, command_id) == 0) {
      return kOpsMap[i].fn(argc, argv);
    }
  }

  yai_porcelain_err_print(YAI_PORCELAIN_ERR_USAGE, "command id not mapped to ops handler yet");
  return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_USAGE);
}