/* SPDX-License-Identifier: Apache-2.0 */
// src/porcelain/porcelain_help.c

#include "yai_cli/porcelain/porcelain_help.h"

#include "yai_cli/law/law_registry.h"
#include "yai_cli/porcelain/porcelain_output.h"
#include "yai_cli/porcelain/porcelain_errors.h"

#include <string.h>
#include <stddef.h>

static int ensure_registry(void) {
  if (yai_law_registry_init() != 0) {
    yai_porcelain_err_print(
      YAI_PORCELAIN_ERR_DEP_MISSING,
      "law registry unavailable (deps/yai-law not readable/valid)"
    );
    return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_DEP_MISSING);
  }

  const yai_law_registry_t* reg = yai_law_registry();
  if (!reg) {
    yai_porcelain_err_print(YAI_PORCELAIN_ERR_DEP_MISSING, "law registry not loaded");
    return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_DEP_MISSING);
  }

  return 0;
}

static const yai_law_registry_t* reg_or_null(void) {
  return yai_law_registry();
}

static int print_global(void) {
  int rc = ensure_registry();
  if (rc != 0) return rc;

  const yai_law_registry_t* reg = reg_or_null();
  if (!reg) return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_DEP_MISSING);

  yai_porcelain_out_heading("YAI CLI (registry-driven) — Help");
  yai_porcelain_out_list_item("yai help");
  yai_porcelain_out_list_item("yai help <group>");
  yai_porcelain_out_list_item("yai help yai.<group>.<name>");
  yai_porcelain_out_list_item("yai law <subcommand> ...");
  yai_porcelain_out_list_item("yai <group> <name> [args...]");

  /* list groups (unique, naive) */
  yai_porcelain_out_heading("Groups");
  for (size_t i = 0; i < reg->commands_len; i++) {
    const char* g = reg->commands[i].group;
    if (!g) continue;

    int seen = 0;
    for (size_t j = 0; j < i; j++) {
      const char* pg = reg->commands[j].group;
      if (pg && strcmp(pg, g) == 0) { seen = 1; break; }
    }
    if (!seen) yai_porcelain_out_list_item(g);
  }

  return 0;
}

static int print_group(const char* group) {
  int rc = ensure_registry();
  if (rc != 0) return rc;

  yai_law_cmd_list_t lst = yai_law_cmds_by_group(group);
  if (!lst.items || lst.len == 0) {
    yai_porcelain_err_print(YAI_PORCELAIN_ERR_USAGE, "unknown group");
    return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_USAGE);
  }

  yai_porcelain_out_heading(group);

  for (size_t i = 0; i < lst.len; i++) {
    const yai_law_command_t* c = lst.items[i];
    if (!c) continue;
    yai_porcelain_out_kv(c->name ? c->name : "(unnamed)",
                         c->summary ? c->summary : "");
  }

  return 0;
}

static int print_command_id(const char* id) {
  int rc = ensure_registry();
  if (rc != 0) return rc;

  const yai_law_command_t* c = yai_law_cmd_by_id(id);
  if (!c) {
    yai_porcelain_err_print(YAI_PORCELAIN_ERR_USAGE, "unknown command id");
    return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_USAGE);
  }

  yai_porcelain_out_heading(c->id ? c->id : "command");
  yai_porcelain_out_kv("name", c->name ? c->name : "");
  yai_porcelain_out_kv("group", c->group ? c->group : "");
  yai_porcelain_out_kv("summary", c->summary ? c->summary : "");

  /* Args */
  yai_porcelain_out_heading("args");
  for (size_t i = 0; i < c->args_len; i++) {
    const yai_law_arg_t* a = &c->args[i];
    if (!a || !a->name) continue;
    yai_porcelain_out_kv(a->name, a->type ? a->type : "");
  }

  /* Uses primitives */
  if (c->uses_primitives && c->uses_primitives_len > 0) {
    yai_porcelain_out_heading("uses_primitives");
    for (size_t i = 0; i < c->uses_primitives_len; i++) {
      if (c->uses_primitives[i]) yai_porcelain_out_list_item(c->uses_primitives[i]);
    }
  }

  /* Emits artifacts */
  if (c->emits_artifacts && c->emits_artifacts_len > 0) {
    yai_porcelain_out_heading("emits_artifacts");
    for (size_t i = 0; i < c->emits_artifacts_len; i++) {
      const yai_law_artifact_io_t* io = &c->emits_artifacts[i];
      if (io->role) yai_porcelain_out_list_item(io->role);
    }
  }

  /* Consumes artifacts */
  if (c->consumes_artifacts && c->consumes_artifacts_len > 0) {
    yai_porcelain_out_heading("consumes_artifacts");
    for (size_t i = 0; i < c->consumes_artifacts_len; i++) {
      const yai_law_artifact_io_t* io = &c->consumes_artifacts[i];
      if (io->role) yai_porcelain_out_list_item(io->role);
    }
  }

  return 0;
}

int yai_porcelain_help_print_any(const char* token) {
  if (!token || token[0] == '\0') return print_global();

  /* canonical command id */
  if (strncmp(token, "yai.", 4) == 0) return print_command_id(token);

  /* otherwise treat as group */
  return print_group(token);
}