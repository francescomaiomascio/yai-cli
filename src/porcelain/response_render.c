/* SPDX-License-Identifier: Apache-2.0 */

#include "yai_cli/porcelain/response_render.h"

#include <stdio.h>

static int render(const yai_exec_result_t *out, int rc, int verbose)
{
  if (!out || !out->status || !out->code_name || !out->reason) return 0;
  FILE *stream = (rc == 0) ? stdout : stderr;

  if (!verbose) {
    fprintf(stream, "yai: %s: %s: %s\n", out->status, out->code_name, out->reason);
    return 1;
  }

  fprintf(stream,
          "yai: %s: %s: %s (command_id=%s, trace_id=%s, target_plane=%s)\n",
          out->status,
          out->code_name,
          out->reason,
          (out->command_id && out->command_id[0]) ? out->command_id : "yai.unknown.unknown",
          out->trace_id ? out->trace_id : "",
          (out->target_plane && out->target_plane[0]) ? out->target_plane : "kernel");
  return 1;
}

int yai_render_exec_short(const yai_exec_result_t *out, int rc)
{
  return render(out, rc, 0);
}

int yai_render_exec_verbose(const yai_exec_result_t *out, int rc)
{
  return render(out, rc, 1);
}
