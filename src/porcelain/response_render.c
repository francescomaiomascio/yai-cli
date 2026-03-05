/* SPDX-License-Identifier: Apache-2.0 */

#include "yai_cli/porcelain/response_render.h"

#include <stdio.h>
#include <string.h>

int yai_render_exec_short(const yai_sdk_reply_t *out, int rc)
{
  if (!out || !out->status[0] || !out->code[0] || !out->reason[0]) return 0;
  FILE *stream = (rc == 0) ? stdout : stderr;
  if (strcmp(out->status, "ok") == 0) {
    fprintf(stream, "yai: %s\n", out->reason);
    return 1;
  }
  if (strcmp(out->status, "nyi") == 0) {
    fprintf(stream, "yai: nyi (%s): %s\n", out->code, out->reason);
    return 1;
  }
  fprintf(stream, "yai: error (%s): %s\n", out->code, out->reason);
  return 1;
}

int yai_render_exec_verbose(const yai_sdk_reply_t *out, int rc, const char *control_call_json)
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
