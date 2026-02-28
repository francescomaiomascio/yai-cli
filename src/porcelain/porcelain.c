/* SPDX-License-Identifier: Apache-2.0 */
// src/porcelain/porcelain.c

#include "yai_cli/porcelain/porcelain.h"
#include "yai_cli/porcelain/porcelain_parse.h"
#include "yai_cli/porcelain/porcelain_help.h"
#include "yai_cli/porcelain/porcelain_errors.h"
#include "yai_cli/ops/ops_dispatch.h"

#include <string.h>

/* Legacy hook: law command stays separate for now */
int yai_cmd_law(int argc, char **argv);

static int is_help_token(const char *s)
{
  return (s &&
          (strcmp(s, "--help") == 0 ||
           strcmp(s, "-h") == 0 ||
           strcmp(s, "help") == 0));
}

/*
 * Help trigger for a resolved command:
 * - yai <group> <cmd> --help
 * - yai <group> <cmd> -h
 * - yai <group> <cmd> help
 *
 * Keep deterministic: only inspect the first argument token (if present).
 */
static int is_helpish_command_invocation(int cmd_argc, char **cmd_argv)
{
  if (cmd_argc <= 0 || !cmd_argv || !cmd_argv[0]) return 0;
  return is_help_token(cmd_argv[0]);
}

static int err_usage_with_hint(const char *detail)
{
  /* enterprise-style: actionable message */
  if (detail && detail[0]) {
    yai_porcelain_err_print(YAI_PORCELAIN_ERR_USAGE, detail);
  } else {
    yai_porcelain_err_print(YAI_PORCELAIN_ERR_USAGE, "invalid arguments");
  }
  /* keep hint minimal (avoid noisy UX) */
  yai_porcelain_err_print(YAI_PORCELAIN_ERR_USAGE, "try: yai help");
  return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_USAGE);
}

int yai_porcelain_run(int argc, char **argv)
{
  yai_porcelain_request_t req;

  int prc = yai_porcelain_parse_argv(argc, argv, &req);
  if (prc != 0) {
    /* parse populates req.error when possible */
    return err_usage_with_hint(req.error);
  }

  switch (req.kind) {
    case YAI_PORCELAIN_KIND_HELP:
      return yai_porcelain_help_print_any(req.help_token);

    case YAI_PORCELAIN_KIND_LAW:
      return yai_cmd_law(req.law_argc, req.law_argv);

    case YAI_PORCELAIN_KIND_COMMAND:
      if (is_helpish_command_invocation(req.cmd_argc, req.cmd_argv)) {
        /* resolved command id -> show contract help */
        return yai_porcelain_help_print_any(req.command_id);
      }
      return yai_ops_dispatch_by_id(req.command_id, req.cmd_argc, req.cmd_argv);

    case YAI_PORCELAIN_KIND_ERROR:
      return err_usage_with_hint(req.error);

    default:
      yai_porcelain_err_print(YAI_PORCELAIN_ERR_GENERIC, "internal error");
      return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_GENERIC);
  }
}