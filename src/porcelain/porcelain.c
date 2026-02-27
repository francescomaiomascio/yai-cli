/* SPDX-License-Identifier: Apache-2.0 */
// src/porcelain/porcelain.c

#include "yai_cli/porcelain/porcelain.h"
#include "yai_cli/porcelain/porcelain_parse.h"
#include "yai_cli/porcelain/porcelain_help.h"
#include "yai_cli/porcelain/porcelain_errors.h"

#include "yai_cli/ops/ops_dispatch.h"

#include <string.h>

/* Legacy hook: law command stays separate for now */
int yai_cmd_law(int argc, char** argv);

static int is_helpish(int argc, char** argv) {
  for (int i = 0; i < argc; i++) {
    if (!argv[i]) continue;
    if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) return 1;
  }
  return 0;
}

int yai_porcelain_run(int argc, char** argv) {
  yai_porcelain_request_t req;

  if (yai_porcelain_parse_argv(argc, argv, &req) != 0) {
    yai_porcelain_err_print(YAI_PORCELAIN_ERR_USAGE, req.error);
    return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_USAGE);
  }

  switch (req.kind) {
    case YAI_PORCELAIN_KIND_HELP:
      return yai_porcelain_help_print_any(req.help_token);

    case YAI_PORCELAIN_KIND_LAW:
      return yai_cmd_law(req.law_argc, req.law_argv);

    case YAI_PORCELAIN_KIND_COMMAND:
      if (is_helpish(req.cmd_argc, req.cmd_argv)) {
        return yai_porcelain_help_print_any(req.command_id);
      }
      /* NEW WORLD: command_id -> ops handler */
      return yai_ops_dispatch_by_id(req.command_id, req.cmd_argc, req.cmd_argv);

    case YAI_PORCELAIN_KIND_ERROR:
      yai_porcelain_err_print(YAI_PORCELAIN_ERR_USAGE, req.error);
      return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_USAGE);

    default:
      yai_porcelain_err_print(YAI_PORCELAIN_ERR_GENERIC, "internal: unknown request kind");
      return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_GENERIC);
  }
}