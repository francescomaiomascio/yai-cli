/* SPDX-License-Identifier: Apache-2.0 */

#include "yai_cli/porcelain/response_render.h"
#include "yai_cli/porcelain/color.h"
#include "yai_cli/porcelain/display_map.h"

#include <stdio.h>
#include <string.h>

static void print_line(FILE *stream, const char *line, const char *color, int use_color)
{
  if (!line) return;
  if (use_color && color) fprintf(stream, "%s%s%s\n", color, line, YAI_COLOR_RESET);
  else fprintf(stream, "%s\n", line);
}

static int build_human_line(const yai_sdk_reply_t *out, const yai_render_opts_t *opts, char *line, size_t line_cap)
{
  yai_display_label_t dl;
  char reason_h[256];
  if (!line || line_cap == 0 || !out) return 0;
  line[0] = '\0';
  yai_display_from_command(
      (opts && opts->command_id) ? opts->command_id : out->command_id,
      (opts) ? opts->argc : 0,
      (opts) ? opts->argv : NULL,
      &dl);
  yai_display_reason_human(out->reason, reason_h, sizeof(reason_h));

  if (strcmp(out->status, "ok") == 0) {
    if (dl.detail[0]) snprintf(line, line_cap, "%s: %s (%s)", dl.scope, dl.action, dl.detail);
    else snprintf(line, line_cap, "%s: %s ok", dl.scope, dl.action);
    return 1;
  }
  if (strcmp(out->status, "nyi") == 0) {
    snprintf(line, line_cap, "NOT_IMPLEMENTED: %s: %s", dl.scope, dl.action);
    return 1;
  }
  if (strcmp(out->code, "SERVER_UNAVAILABLE") == 0) {
    snprintf(line, line_cap, "SERVER_UNAVAILABLE: root socket unreachable");
    return 1;
  }
  snprintf(line, line_cap, "%s: %s", out->code, reason_h);
  return 1;
}

int yai_render_exec_short(const yai_sdk_reply_t *out, int rc, const yai_render_opts_t *opts)
{
  char line[512];
  const char *color = NULL;
  int use_color;
  FILE *stream = (rc == 0) ? stdout : stderr;
  if (!out || !out->status[0] || !out->code[0] || !out->reason[0]) return 0;
  if (!build_human_line(out, opts, line, sizeof(line))) return 0;

  use_color = (opts && opts->use_color) ? 1 : 0;
  if (strcmp(out->status, "ok") == 0) color = YAI_COLOR_GREEN;
  else if (strcmp(out->status, "nyi") == 0) color = YAI_COLOR_YELLOW;
  else color = YAI_COLOR_RED;
  print_line(stream, line, color, use_color);
  return 1;
}

int yai_render_exec_verbose(const yai_sdk_reply_t *out, int rc, const yai_render_opts_t *opts)
{
  FILE *stream = (rc == 0) ? stdout : stderr;
  char line[512];
  int use_color = (opts && opts->use_color) ? 1 : 0;
  if (!out || !out->status[0] || !out->code[0] || !out->reason[0]) return 0;
  if (!build_human_line(out, opts, line, sizeof(line))) return 0;

  print_line(stream, line,
             (strcmp(out->status, "ok") == 0) ? YAI_COLOR_GREEN :
             (strcmp(out->status, "nyi") == 0) ? YAI_COLOR_YELLOW : YAI_COLOR_RED,
             use_color);
  if (use_color) fprintf(stream, "%sstatus%s=%s\n", YAI_COLOR_CYAN, YAI_COLOR_RESET, out->status);
  else fprintf(stream, "status=%s\n", out->status);
  if (use_color) fprintf(stream, "%scode%s=%s\n", YAI_COLOR_CYAN, YAI_COLOR_RESET, out->code);
  else fprintf(stream, "code=%s\n", out->code);
  if (use_color) fprintf(stream, "%sreason%s=%s\n", YAI_COLOR_CYAN, YAI_COLOR_RESET, out->reason);
  else fprintf(stream, "reason=%s\n", out->reason);
  if (use_color) fprintf(stream, "%scommand_id%s=%s\n", YAI_COLOR_CYAN, YAI_COLOR_RESET, out->command_id);
  else fprintf(stream, "command_id=%s\n", out->command_id);
  if (use_color) fprintf(stream, "%starget_plane%s=%s\n", YAI_COLOR_CYAN, YAI_COLOR_RESET, out->target_plane);
  else fprintf(stream, "target_plane=%s\n", out->target_plane);
  if (use_color) fprintf(stream, "%strace_id%s=%s\n", YAI_COLOR_CYAN, YAI_COLOR_RESET, out->trace_id);
  else fprintf(stream, "trace_id=%s\n", out->trace_id);
  return 1;
}

int yai_render_exec_contract_verbose(const yai_sdk_reply_t *out, int rc, const char *control_call_json)
{
  if (!out || !out->exec_reply_json) return 0;
  FILE *stream = (rc == 0) ? stdout : stderr;
  fprintf(stream, "control_call: %s\n", control_call_json ? control_call_json : "{}");
  fprintf(stream, "exec_reply: %s\n", out->exec_reply_json);
  return 1;
}

int yai_render_exec_json(const yai_sdk_reply_t *out)
{
  if (!out || !out->exec_reply_json) return 0;
  printf("%s\n", out->exec_reply_json);
  return 1;
}

int yai_render_exec_exit_code(const yai_sdk_reply_t *out, int sdk_rc)
{
  if (!out || !out->status[0] || !out->code[0]) {
    return (sdk_rc == 0) ? 0 : 50;
  }
  if (strcmp(out->status, "ok") == 0 && strcmp(out->code, "OK") == 0) return 0;
  if (strcmp(out->status, "nyi") == 0 || strcmp(out->code, "NOT_IMPLEMENTED") == 0) return 10;
  if (strcmp(out->code, "BAD_ARGS") == 0 || strcmp(out->code, "INVALID_TARGET") == 0) return 20;
  if (strcmp(out->code, "UNAUTHORIZED") == 0) return 30;
  if (strcmp(out->code, "SERVER_UNAVAILABLE") == 0 || strcmp(out->code, "RUNTIME_NOT_READY") == 0) return 40;
  return 50;
}
