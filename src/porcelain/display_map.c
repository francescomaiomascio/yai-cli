/* SPDX-License-Identifier: Apache-2.0 */

#include "yai_cli/porcelain/display_map.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

static const char *find_flag_value(int argc, char **argv, const char *a, const char *b)
{
  for (int i = 0; i + 1 < argc; i++) {
    if (!argv || !argv[i] || !argv[i + 1]) continue;
    if ((a && strcmp(argv[i], a) == 0) || (b && strcmp(argv[i], b) == 0)) {
      return argv[i + 1];
    }
  }
  return NULL;
}

void yai_display_reason_human(const char *reason, char *out, size_t out_cap)
{
  size_t j = 0;
  if (!out || out_cap == 0) return;
  out[0] = '\0';
  if (!reason || !reason[0]) {
    snprintf(out, out_cap, "operation failed");
    return;
  }
  for (size_t i = 0; reason[i] && j + 1 < out_cap; i++) {
    char ch = reason[i];
    if (ch == '_') ch = ' ';
    out[j++] = (char)tolower((unsigned char)ch);
  }
  out[j] = '\0';
}

void yai_display_from_command(const char *command_id, int argc, char **argv, yai_display_label_t *out)
{
  const char *ws_id = NULL;
  if (!out) return;
  memset(out, 0, sizeof(*out));
  snprintf(out->scope, sizeof(out->scope), "command");
  snprintf(out->action, sizeof(out->action), "%s", (command_id && command_id[0]) ? command_id : "unknown");
  out->detail[0] = '\0';

  if (!command_id || !command_id[0]) return;

  if (strcmp(command_id, "yai.root.ping") == 0) {
    snprintf(out->scope, sizeof(out->scope), "root");
    snprintf(out->action, sizeof(out->action), "ping");
    return;
  }
  if (strcmp(command_id, "yai.kernel.ping") == 0) {
    snprintf(out->scope, sizeof(out->scope), "kernel");
    snprintf(out->action, sizeof(out->action), "ping");
    return;
  }
  if (strcmp(command_id, "yai.lifecycle.up") == 0 ||
      strcmp(command_id, "yai.lifecycle.down") == 0 ||
      strcmp(command_id, "yai.lifecycle.restart") == 0) {
    snprintf(out->scope, sizeof(out->scope), "lifecycle");
    snprintf(out->action, sizeof(out->action), "%s", strrchr(command_id, '.') + 1);
    return;
  }
  if (strcmp(command_id, "yai.kernel.ws") == 0) {
    snprintf(out->scope, sizeof(out->scope), "kernel");
    if (argc > 0 && argv && argv[0]) {
      if (strcmp(argv[0], "create") == 0) snprintf(out->action, sizeof(out->action), "ws created");
      else if (strcmp(argv[0], "reset") == 0) snprintf(out->action, sizeof(out->action), "ws reset");
      else if (strcmp(argv[0], "destroy") == 0) snprintf(out->action, sizeof(out->action), "ws destroyed");
      else snprintf(out->action, sizeof(out->action), "ws %s", argv[0]);
    } else {
      snprintf(out->action, sizeof(out->action), "ws");
    }
    ws_id = find_flag_value(argc, argv, "--ws-id", "--ws");
    if (ws_id && ws_id[0]) {
      snprintf(out->detail, sizeof(out->detail), "ws_id=%s", ws_id);
    }
    return;
  }
  if (strcmp(command_id, "yai.kernel.ws_status") == 0) {
    snprintf(out->scope, sizeof(out->scope), "kernel");
    snprintf(out->action, sizeof(out->action), "ws status");
    ws_id = find_flag_value(argc, argv, "--ws-id", "--ws");
    if (ws_id && ws_id[0]) snprintf(out->detail, sizeof(out->detail), "ws_id=%s", ws_id);
    return;
  }
  if (strcmp(command_id, "yai.kernel.ws_list") == 0) {
    snprintf(out->scope, sizeof(out->scope), "kernel");
    snprintf(out->action, sizeof(out->action), "ws list");
    return;
  }

  /* fallback: yai.<scope>.<verb> */
  {
    const char *p = command_id;
    const char *d1 = strchr(p, '.');
    const char *d2 = d1 ? strchr(d1 + 1, '.') : NULL;
    if (d1 && d2 && d2[1]) {
      size_t sl = (size_t)(d2 - (d1 + 1));
      if (sl > 0 && sl < sizeof(out->scope)) {
        memcpy(out->scope, d1 + 1, sl);
        out->scope[sl] = '\0';
      }
      snprintf(out->action, sizeof(out->action), "%s", d2 + 1);
      for (size_t i = 0; out->action[i]; i++) {
        if (out->action[i] == '_') out->action[i] = ' ';
      }
    }
  }
}

