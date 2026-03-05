/* SPDX-License-Identifier: Apache-2.0 */
// src/porcelain/porcelain.c

#include "yai_cli/porcelain/porcelain.h"
#include "yai_cli/porcelain/porcelain_parse.h"
#include "yai_cli/porcelain/porcelain_help.h"
#include "yai_cli/porcelain/porcelain_errors.h"
#include "yai_cli/porcelain/response_render.h"
#include "yai_cli/porcelain/control_call_build.h"
#include "yai_cli/porcelain/lifecycle.h"
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
        yai_sdk_reply_t reply = {0};
        int sdk_rc = 0;
        char *control_call_json = NULL;

        if (strcmp(req.command_id, "yai.lifecycle.up") == 0 ||
            strcmp(req.command_id, "yai.lifecycle.down") == 0 ||
            strcmp(req.command_id, "yai.lifecycle.restart") == 0) {
          sdk_rc = yai_cli_lifecycle_run(req.command_id, &reply);
        } else {
          control_call_json = yai_build_control_call_json(req.command_id, req.cmd_argc, req.cmd_argv);
          if (!control_call_json) {
            yai_porcelain_err_print(YAI_PORCELAIN_ERR_GENERIC, "cannot build control_call json");
            return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_GENERIC);
          }

          yai_sdk_client_opts_t opts = {
            .ws_id = req.ws_id ? req.ws_id : "default",
            .uds_path = NULL,
            .arming = req.arming,
            .role = req.role ? req.role : "operator",
            .auto_handshake = 1,
          };
          yai_sdk_client_t *client = NULL;
          sdk_rc = yai_sdk_client_open(&client, &opts);
          if (sdk_rc == 0) {
            if (strcmp(req.command_id, "yai.root.ping") == 0 ||
                strcmp(req.command_id, "yai.kernel.ping") == 0) {
              sdk_rc = yai_sdk_client_ping(client, req.command_id, &reply);
            } else {
              sdk_rc = yai_sdk_client_call_json(client, control_call_json, &reply);
            }
            yai_sdk_client_close(client);
          } else {
            snprintf(reply.status, sizeof(reply.status), "error");
            snprintf(reply.code, sizeof(reply.code), "SERVER_UNAVAILABLE");
            snprintf(reply.reason, sizeof(reply.reason), "server_unavailable");
            snprintf(reply.command_id, sizeof(reply.command_id), "%s", req.command_id);
            snprintf(reply.target_plane, sizeof(reply.target_plane), "%s", "root");
          }
        }

        int rendered = 0;
        if (req.json_output) {
          rendered = yai_render_exec_json(&reply);
        } else if (req.verbose_contract) {
          rendered = yai_render_exec_verbose(&reply, sdk_rc, control_call_json);
        } else {
          rendered = yai_render_exec_short(&reply, sdk_rc);
        }
        if (!rendered) {
          yai_porcelain_err_print(YAI_PORCELAIN_ERR_GENERIC, "execution failed");
          free(control_call_json);
          yai_sdk_reply_free(&reply);
          return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_GENERIC);
        }
        int exit_code = yai_render_exec_exit_code(&reply, sdk_rc);
        free(control_call_json);
        yai_sdk_reply_free(&reply);
        return exit_code;
      }

    case YAI_PORCELAIN_KIND_ERROR:
      return err_usage_with_hint(req.error);

    default:
      yai_porcelain_err_print(YAI_PORCELAIN_ERR_GENERIC, "internal error");
      return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_GENERIC);
  }
}
