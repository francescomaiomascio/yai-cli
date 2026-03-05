/* SPDX-License-Identifier: Apache-2.0 */
// src/porcelain/porcelain.c

#include "yai_cli/porcelain/porcelain.h"
#include "yai_cli/porcelain/porcelain_parse.h"
#include "yai_cli/porcelain/porcelain_help.h"
#include "yai_cli/porcelain/porcelain_errors.h"
#include "yai_sdk/public.h"

#include <stdio.h>
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

static int print_normalized_exec_error(const char *msg)
{
  if (!msg || !msg[0]) return 0;

  const char *pfx = "yai-sdk: ";
  size_t pfx_len = strlen(pfx);
  if (strncmp(msg, pfx, pfx_len) != 0) return 0;

  const char *payload = msg + pfx_len;
  const char *c1 = strchr(payload, ':');
  if (!c1) return 0;
  const char *c2 = strchr(c1 + 1, ':');
  if (!c2) return 0;

  char status[24] = {0};
  char code[64] = {0};
  char reason[192] = {0};
  size_t s_len = (size_t)(c1 - payload);
  size_t code_len = (size_t)(c2 - (c1 + 1));
  if (s_len == 0 || s_len >= sizeof(status) || code_len == 0 || code_len >= sizeof(code)) return 0;

  memcpy(status, payload, s_len);
  memcpy(code, c1 + 1, code_len);
  snprintf(reason, sizeof(reason), "%s", c2 + 1);
  fprintf(stderr, "yai: %s: %s: %s\n", status, code, reason);
  return 1;
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
      {
        yai_exec_request_t sdk_req = {
          .command_id = req.command_id,
          .argc = req.cmd_argc,
          .argv = (const char **)req.cmd_argv,
          .json_mode = 1,
        };
        yai_exec_result_t out = {0};
        int rc = yai_sdk_execute(&sdk_req, &out);
        if (rc != 0 && out.message && out.message[0]) {
          if (!print_normalized_exec_error(out.message)) {
            yai_porcelain_err_print(YAI_PORCELAIN_ERR_GENERIC, out.message);
          }
        }
        return rc;
      }

    case YAI_PORCELAIN_KIND_ERROR:
      return err_usage_with_hint(req.error);

    default:
      yai_porcelain_err_print(YAI_PORCELAIN_ERR_GENERIC, "internal error");
      return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_GENERIC);
  }
}
