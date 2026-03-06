/* SPDX-License-Identifier: Apache-2.0 */
// src/porcelain/porcelain.c

#include "yai_cli/porcelain/porcelain.h"
#include "yai_cli/porcelain/porcelain_parse.h"
#include "yai_cli/porcelain/porcelain_help.h"
#include "yai_cli/porcelain/porcelain_errors.h"
#include "yai_cli/porcelain/response_render.h"
#include "yai_sdk/public.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

static int command_has_ws_flag(int argc, char **argv)
{
  for (int i = 0; i + 1 < argc; i++) {
    if (!argv || !argv[i]) continue;
    if ((strcmp(argv[i], "--ws-id") == 0 || strcmp(argv[i], "--ws") == 0) &&
        argv[i + 1] && argv[i + 1][0]) {
      return 1;
    }
  }
  return 0;
}

static int command_requires_workspace(const char *command_id)
{
  if (!command_id || !command_id[0]) return 0;
  return (
    strncmp(command_id, "yai.governance.", 15) == 0 ||
    strncmp(command_id, "yai.inspect.", 12) == 0 ||
    strncmp(command_id, "yai.verify.", 11) == 0 ||
    strncmp(command_id, "yai.bundle.", 11) == 0 ||
    strncmp(command_id, "yai.kernel.ws", 13) == 0
  );
}

static int handle_ws_use(const char *ws_id)
{
  yai_sdk_workspace_info_t info = {0};
  int rc = yai_sdk_workspace_describe(ws_id, &info);
  if (rc != 0 || !info.exists) {
    fprintf(stderr, "ws use\nFAILED\nWorkspace '%s' is not available.\nHint: Run: yai kernel ws_status --ws-id %s\n", ws_id, ws_id);
    return YAI_SDK_BAD_ARGS;
  }
  rc = yai_sdk_context_set_current_workspace(ws_id);
  if (rc != 0) {
    fprintf(stderr, "ws use\nFAILED\nUnable to persist current workspace binding.\n");
    return rc;
  }
  printf("ws use\nOK\nCurrent workspace set to '%s'.\n", ws_id);
  return 0;
}

static int handle_ws_current(void)
{
  yai_sdk_workspace_info_t info = {0};
  int rc = yai_sdk_context_validate_current_workspace(&info);
  if (rc == YAI_SDK_BAD_ARGS) {
    fprintf(stderr, "ws current\nBAD ARGS\nNo workspace selected.\nHint: Run: yai ws use <ws-id>\n");
    return rc;
  }
  if (rc != 0) {
    fprintf(stderr, "ws current\nFAILED\nCurrent workspace is no longer available.\nHint: Run: yai ws clear\n");
    return rc;
  }

  printf("ws current\nOK\nws_id=%s\nstate=%s\nroot_path=%s\n",
         info.ws_id[0] ? info.ws_id : "unknown",
         info.state[0] ? info.state : "unknown",
         info.root_path[0] ? info.root_path : "-");
  return 0;
}

static int handle_ws_clear(void)
{
  int rc = yai_sdk_context_clear_current_workspace();
  if (rc != 0) {
    fprintf(stderr, "ws clear\nFAILED\nUnable to clear current workspace binding.\n");
    return rc;
  }
  printf("ws clear\nOK\nCurrent workspace binding cleared.\n");
  return 0;
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
        const char **argv_eff = (const char **)req.cmd_argv;
        int argc_eff = req.cmd_argc;
        const char *resolved_ws = NULL;
        char ws_buf[64] = {0};
        const char *augmented[256];

        if (command_requires_workspace(req.command_id) && !command_has_ws_flag(req.cmd_argc, req.cmd_argv)) {
          if (yai_sdk_context_resolve_workspace(NULL, ws_buf, sizeof(ws_buf)) == 0 && ws_buf[0]) {
            resolved_ws = ws_buf;
          } else {
            fprintf(stderr, "%s\nBAD ARGS\nNo workspace selected.\nHint: Run: yai ws use <ws-id>\nHint: Or pass: --ws-id <ws-id>\n",
                    req.command_id ? req.command_id : "command");
            return YAI_SDK_BAD_ARGS;
          }
        }

        if (resolved_ws) {
          if (req.cmd_argc + 2 >= (int)(sizeof(augmented) / sizeof(augmented[0]))) {
            return YAI_SDK_BAD_ARGS;
          }
          for (int i = 0; i < req.cmd_argc; i++) {
            augmented[i] = req.cmd_argv[i];
          }
          augmented[req.cmd_argc] = "--ws-id";
          augmented[req.cmd_argc + 1] = resolved_ws;
          argv_eff = augmented;
          argc_eff = req.cmd_argc + 2;
        }

        yai_exec_request_t sdk_req = {
          .command_id = req.command_id,
          .argc = argc_eff,
          .argv = argv_eff,
          .json_mode = 1,
        };
        yai_exec_result_t out = {0};
        int rc = yai_sdk_execute(&sdk_req, &out);
        int rendered = req.verbose_contract
                         ? yai_render_exec_verbose(&out, rc)
                         : yai_render_exec_short(&out, rc);
        if (!rendered && rc != 0) {
          yai_porcelain_err_print(YAI_PORCELAIN_ERR_GENERIC, out.message ? out.message : "execution failed");
        }
        return rc;
      }

    case YAI_PORCELAIN_KIND_WS_USE:
      return handle_ws_use(req.ws_id);

    case YAI_PORCELAIN_KIND_WS_CURRENT:
      return handle_ws_current();

    case YAI_PORCELAIN_KIND_WS_CLEAR:
      return handle_ws_clear();

    case YAI_PORCELAIN_KIND_ERROR:
      return err_usage_with_hint(req.error);

    default:
      yai_porcelain_err_print(YAI_PORCELAIN_ERR_GENERIC, "internal error");
      return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_GENERIC);
  }
}
