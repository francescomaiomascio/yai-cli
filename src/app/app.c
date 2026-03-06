/* SPDX-License-Identifier: Apache-2.0 */
// src/app/app.c

#include "yai_cli/app.h"
#include "yai_cli/parse.h"
#include "yai_cli/help.h"
#include "yai_cli/errors.h"
#include "yai_cli/render.h"
#include "yai_cli/display_map.h"
#include "yai_cli/control_call.h"
#include "yai_cli/lifecycle.h"
#include "yai_cli/color.h"
#include "yai_cli/watch.h"
#include "yai_cli/term.h"
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

static void ensure_exec_reply_json(yai_sdk_reply_t *reply)
{
  char buf[768];
  yai_display_result_t mapped;
  yai_display_from_reply(reply, &mapped);
  size_t len;
  int n;
  if (!reply || reply->exec_reply_json) return;
  n = snprintf(buf, sizeof(buf),
               "{\"type\":\"yai.exec.reply.v1\",\"status\":\"%s\",\"code\":\"%s\",\"reason\":\"%s\",\"summary\":\"%s\",\"command_id\":\"%s\",\"target_plane\":\"%s\",\"trace_id\":\"%s\"}",
               reply->status[0] ? reply->status : "error",
               reply->code[0] ? reply->code : "INTERNAL_ERROR",
               reply->reason[0] ? reply->reason : "internal_error",
               mapped.detail[0] ? mapped.detail : "Command failed.",
               reply->command_id[0] ? reply->command_id : "yai.unknown.unknown",
               reply->target_plane[0] ? reply->target_plane : "kernel",
               reply->trace_id);
  if (n > 0 && (size_t)n < sizeof(buf)) {
    len = (size_t)n;
    reply->exec_reply_json = (char *)malloc(len + 1);
    if (reply->exec_reply_json) {
      memcpy(reply->exec_reply_json, buf, len + 1);
    }
  }
}

static int err_usage_with_hint(const char *detail, const char *hint, int verbose_contract)
{
  (void)verbose_contract;
  fprintf(stderr, "command line\n");
  fprintf(stderr, "BAD ARGS\n");
  fprintf(stderr, "%s\n", (detail && detail[0]) ? detail : "invalid invocation");
  if (hint && hint[0]) fprintf(stderr, "Hint: %s\n", hint);
  return 20;
}

int yai_porcelain_run(int argc, char **argv)
{
  yai_porcelain_request_t req;

  int prc = yai_porcelain_parse_argv(argc, argv, &req);
  if (prc != 0) {
    return err_usage_with_hint(req.error, req.error_hint, req.verbose_contract);
  }

  switch (req.kind) {
    case YAI_PORCELAIN_KIND_HELP:
      {
        int hrc = yai_porcelain_help_print(req.help_token, req.help_token2, req.help_token3, req.pager, req.no_pager);
        if (req.help_exit_code != 0) return req.help_exit_code;
        return hrc;
      }

    case YAI_PORCELAIN_KIND_LAW:
      return yai_cmd_law(req.law_argc, req.law_argv);

    case YAI_PORCELAIN_KIND_COMMAND:
      if (is_helpish_command_invocation(req.cmd_argc, req.cmd_argv)) {
        /* resolved command id -> show contract help */
        return yai_porcelain_help_print(req.command_id, NULL, NULL, req.pager, req.no_pager);
      }
      if (req.interactive && !yai_term_is_tty()) {
        yai_porcelain_err_print(YAI_PORCELAIN_ERR_USAGE, "--interactive requires a TTY");
        return 20;
      }
      {
        yai_sdk_reply_t reply = {0};
        int sdk_rc = 0;
        char *control_call_json = yai_build_control_call_json(req.command_id, req.cmd_argc, req.cmd_argv);
        if (!control_call_json) {
          fprintf(stderr, "command execution\n");
          fprintf(stderr, "INTERNAL ERROR\n");
          fprintf(stderr, "cannot build control_call json\n");
          return 50;
        }

        if (strcmp(req.command_id, "yai.lifecycle.up") == 0 ||
            strcmp(req.command_id, "yai.lifecycle.down") == 0 ||
            strcmp(req.command_id, "yai.lifecycle.restart") == 0) {
          sdk_rc = yai_cli_lifecycle_run(req.command_id, &reply);
        } else {
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
        ensure_exec_reply_json(&reply);

        int rendered = 0;
        yai_render_opts_t ropts = {
          .use_color = yai_color_enabled((sdk_rc == 0) ? stdout : stderr, req.no_color, req.color_mode),
          .is_tty = yai_term_is_tty(),
          .show_trace = req.show_trace,
          .quiet = req.quiet,
          .command_id = req.command_id,
          .argc = req.cmd_argc,
          .argv = req.cmd_argv,
        };
        if (req.json_output) {
          rendered = yai_render_exec_json(&reply);
        } else if (req.verbose_contract) {
          rendered = yai_render_exec_contract_verbose(&reply, sdk_rc, control_call_json);
        } else if (req.verbose) {
          rendered = yai_render_exec_verbose(&reply, sdk_rc, &ropts);
        } else {
          rendered = yai_render_exec_short(&reply, sdk_rc, &ropts);
        }
        if (!rendered) {
          fprintf(stderr, "command execution\n");
          fprintf(stderr, "INTERNAL ERROR\n");
          fprintf(stderr, "execution failed\n");
          free(control_call_json);
          yai_sdk_reply_free(&reply);
          return 50;
        }
        int exit_code = yai_render_exec_exit_code(&reply, sdk_rc);
        free(control_call_json);
        yai_sdk_reply_free(&reply);
        return exit_code;
      }

    case YAI_PORCELAIN_KIND_WATCH:
      if (req.interactive && !yai_term_is_tty()) {
        yai_porcelain_err_print(YAI_PORCELAIN_ERR_USAGE, "--interactive requires a TTY");
        return 20;
      }
      return yai_watch_mode_run(req.cmd_argc, req.cmd_argv, req.watch_interval_ms, req.watch_count, req.watch_no_clear, req.no_color);

    case YAI_PORCELAIN_KIND_ERROR:
      return err_usage_with_hint(req.error, req.error_hint, req.verbose_contract);

    default:
      fprintf(stderr, "command line\n");
      fprintf(stderr, "INTERNAL ERROR\n");
      fprintf(stderr, "internal error\n");
      return 50;
  }
}
