/* SPDX-License-Identifier: Apache-2.0 */

#include "yai_cli/render.h"
#include "yai_cli/display_map.h"
#include "yai_cli/color.h"
#include "yai_cli/style_map.h"

#include <stdio.h>
#include <string.h>

static void print_line(FILE *stream, const char *line, int color_enabled, const char *color)
{
  if (!line) return;
  yai_color_print(stream, color_enabled, color, line);
  fputc('\n', stream);
}

static int build_subject(const yai_render_opts_t *opts, const yai_sdk_reply_t *out, char *line, size_t line_cap)
{
  yai_display_label_t dl;
  if (!line || line_cap == 0 || !out) return 0;
  line[0] = '\0';
  yai_display_from_command(
      (opts && opts->command_id) ? opts->command_id : out->command_id,
      (opts) ? opts->argc : 0,
      (opts) ? opts->argv : NULL,
      &dl);
  snprintf(line, line_cap, "%s %s", dl.scope, dl.action);
  return 1;
}

int yai_render_exec_short(const yai_sdk_reply_t *out, int rc, const yai_render_opts_t *opts)
{
  char subject[256];
  yai_display_result_t mapped;
  int use_color;
  yai_style_role_t status_role = YAI_STYLE_INFO;
  FILE *stream = (rc == 0) ? stdout : stderr;
  if (!out || !out->status[0] || !out->code[0] || !out->reason[0]) return 0;
  if (!build_subject(opts, out, subject, sizeof(subject))) return 0;
  yai_display_from_reply(out, &mapped);

  use_color = (opts && opts->use_color) ? 1 : 0;
  if (strcmp(out->status, "ok") == 0) status_role = YAI_STYLE_OK;
  else if (strcmp(out->status, "nyi") == 0 || strcmp(out->code, "RUNTIME_NOT_READY") == 0) status_role = YAI_STYLE_WARN;
  else status_role = YAI_STYLE_ERR;

  print_line(stream, subject, use_color, yai_style_color(YAI_STYLE_EMPH));
  print_line(stream, mapped.status_label, use_color, yai_style_color(status_role));
  if (mapped.detail[0]) fprintf(stream, "%s\n", mapped.detail);
  if (out->trace_id[0] && ((opts && opts->show_trace) || strcmp(out->status, "ok") != 0)) {
    yai_color_print(stream, use_color, yai_style_color(YAI_STYLE_MUTED), "Trace: ");
    fprintf(stream, "%s\n", out->trace_id);
  }
  if (!(opts && opts->quiet) && mapped.hint[0] && strcmp(out->status, "ok") != 0) {
    fprintf(stream, "Hint: %s\n", mapped.hint);
  }
  return 1;
}

int yai_render_exec_verbose(const yai_sdk_reply_t *out, int rc, const yai_render_opts_t *opts)
{
  yai_display_result_t mapped;
  FILE *stream = (rc == 0) ? stdout : stderr;
  char subject[256];
  int use_color = (opts && opts->use_color) ? 1 : 0;
  yai_style_role_t status_role = YAI_STYLE_INFO;
  if (!out || !out->status[0] || !out->code[0] || !out->reason[0]) return 0;
  if (!build_subject(opts, out, subject, sizeof(subject))) return 0;
  yai_display_from_reply(out, &mapped);

  if (strcmp(out->status, "ok") == 0) status_role = YAI_STYLE_OK;
  else if (strcmp(out->status, "nyi") == 0 || strcmp(out->code, "RUNTIME_NOT_READY") == 0) status_role = YAI_STYLE_WARN;
  else status_role = YAI_STYLE_ERR;
  print_line(stream, subject, use_color, yai_style_color(YAI_STYLE_EMPH));
  print_line(stream, mapped.status_label, use_color, yai_style_color(status_role));
  yai_color_print(stream, use_color, yai_style_color(YAI_STYLE_INFO), "Details:");
  fputc('\n', stream);
  if (mapped.detail[0]) fprintf(stream, "  %s\n", mapped.detail);
  fprintf(stream, "  status=%s\n", out->status);
  fprintf(stream, "  code=%s\n", out->code);
  fprintf(stream, "  reason=%s\n", out->reason);
  fprintf(stream, "  command_id=%s\n", out->command_id);
  fprintf(stream, "  target_plane=%s\n", out->target_plane);
  if (out->trace_id[0]) {
    yai_color_print(stream, use_color, yai_style_color(YAI_STYLE_MUTED), "Trace: ");
    fprintf(stream, "%s\n", out->trace_id);
  }
  if (mapped.hint[0] && strcmp(out->status, "ok") != 0) fprintf(stream, "Hint: %s\n", mapped.hint);
  return 1;
}

int yai_render_exec_contract_verbose(const yai_sdk_reply_t *out, int rc, const char *control_call_json)
{
  FILE *stream = (rc == 0) ? stdout : stderr;
  if (!out || !out->exec_reply_json) return 0;
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
