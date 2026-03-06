/* SPDX-License-Identifier: Apache-2.0 */

#include "yai_cli/display_map.h"

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
      if (strcmp(argv[0], "create") == 0) snprintf(out->action, sizeof(out->action), "ws create");
      else if (strcmp(argv[0], "reset") == 0) snprintf(out->action, sizeof(out->action), "ws reset");
      else if (strcmp(argv[0], "destroy") == 0) snprintf(out->action, sizeof(out->action), "ws destroy");
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

void yai_display_from_reply(const yai_sdk_reply_t *reply, yai_display_result_t *out)
{
  if (!out) return;
  memset(out, 0, sizeof(*out));
  if (!reply) {
    snprintf(out->status_label, sizeof(out->status_label), "INTERNAL ERROR");
    snprintf(out->detail, sizeof(out->detail), "reply missing");
    snprintf(out->hint, sizeof(out->hint), "Try: yai help");
    return;
  }

  if (strcmp(reply->status, "ok") == 0 && strcmp(reply->code, "OK") == 0) {
    snprintf(out->status_label, sizeof(out->status_label), "OK");
    return;
  }
  if (strcmp(reply->status, "nyi") == 0 || strcmp(reply->code, "NOT_IMPLEMENTED") == 0) {
    snprintf(out->status_label, sizeof(out->status_label), "NOT IMPLEMENTED");
    snprintf(out->detail, sizeof(out->detail), "This command is registered but not implemented yet.");
    snprintf(out->hint, sizeof(out->hint), "Try: yai help <group>");
    return;
  }
  if (strcmp(reply->code, "BAD_ARGS") == 0 || strcmp(reply->code, "INVALID_TARGET") == 0) {
    snprintf(out->status_label, sizeof(out->status_label), "BAD ARGS");
    snprintf(out->detail, sizeof(out->detail), "The command arguments are invalid.");
    snprintf(out->hint, sizeof(out->hint), "Try: yai help <group> <command>");
    return;
  }
  if (strcmp(reply->code, "UNAUTHORIZED") == 0) {
    snprintf(out->status_label, sizeof(out->status_label), "UNAUTHORIZED");
    snprintf(out->detail, sizeof(out->detail), "Operation blocked by authority policy.");
    snprintf(out->hint, sizeof(out->hint), "Check authority/role configuration");
    return;
  }
  if (strcmp(reply->code, "RUNTIME_NOT_READY") == 0) {
    snprintf(out->status_label, sizeof(out->status_label), "RUNTIME NOT READY");
    snprintf(out->detail, sizeof(out->detail), "Runtime is up but not ready for control calls.");
    snprintf(out->hint, sizeof(out->hint), "Try: yai root handshake_status");
    return;
  }
  if (strcmp(reply->code, "SERVER_UNAVAILABLE") == 0) {
    snprintf(out->status_label, sizeof(out->status_label), "SERVER UNAVAILABLE");
    if (strstr(reply->reason, "root_socket") != NULL) {
      snprintf(out->detail, sizeof(out->detail), "Root socket is unreachable.");
    } else {
      snprintf(out->detail, sizeof(out->detail), "Runtime endpoint is unreachable.");
    }
    snprintf(out->hint, sizeof(out->hint), "Start the runtime with: yai lifecycle up");
    return;
  }
  if (strcmp(reply->code, "PROTOCOL_ERROR") == 0) {
    snprintf(out->status_label, sizeof(out->status_label), "PROTOCOL ERROR");
    snprintf(out->detail, sizeof(out->detail), "Reply payload is not compliant with exec_reply.v1.");
    snprintf(out->hint, sizeof(out->hint), "Try again with --verbose-contract and attach control_call/exec_reply");
    return;
  }

  snprintf(out->status_label, sizeof(out->status_label), "INTERNAL ERROR");
  snprintf(out->detail, sizeof(out->detail), "Unexpected runtime failure.");
  snprintf(out->hint, sizeof(out->hint), "Try again with --verbose-contract and attach control_call/exec_reply");
}
