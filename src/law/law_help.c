// src/law/law_help.c
#include "yai_cli/law/law_help.h"

#include "yai_cli/law/law_registry.h"
#include "yai_cli/support/fmt.h"

#include <stdio.h>
#include <string.h>

static void print_header(const char* title) {
  printf("%s\n", title);
}

static void print_cmd_line(const yai_law_command_t* c) {
  if (!c) return;
  // "yai <group> <name>" style, but keep the canonical id visible.
  // Example: "yai verify verify   (yai.verify.verify)  - Run verification gates"
  printf("  yai %-10s %-14s  (%s)\n", c->group ? c->group : "-", c->name ? c->name : "-", c->id ? c->id : "-");
  printf("      %s\n", c->summary ? c->summary : "");
}

static void print_args(const yai_law_command_t* c) {
  if (!c) return;
  if (c->args_len == 0) {
    printf("  Args: (none)\n");
    return;
  }

  printf("  Args:\n");
  for (size_t i = 0; i < c->args_len; i++) {
    const yai_law_arg_t* a = &c->args[i];
    if (!a->name || !a->type) continue;

    // positional
    if (a->pos > 0) {
      printf("    #%d  %s : %s", a->pos, a->name, a->type);
    } else if (a->flag) {
      printf("    %s  %s : %s", a->flag, a->name, a->type);
    } else {
      printf("    %s : %s", a->name, a->type);
    }

    if (a->required) printf("  [required]");
    printf("\n");

    if (a->values_len > 0 && a->values) {
      printf("         values: ");
      for (size_t k = 0; k < a->values_len; k++) {
        printf("%s%s", a->values[k] ? a->values[k] : "", (k + 1 < a->values_len) ? ", " : "");
      }
      printf("\n");
    }
  }
}

static void print_list_str(const char* label, const char* const* items, size_t len) {
  if (!items || len == 0) return;
  printf("  %s: ", label);
  for (size_t i = 0; i < len; i++) {
    printf("%s%s", items[i] ? items[i] : "", (i + 1 < len) ? ", " : "");
  }
  printf("\n");
}

static void print_art_ios(const yai_law_registry_t* r, const char* label, const yai_law_artifact_io_t* ios, size_t len) {
  (void)r;
  if (!ios || len == 0) return;

  printf("  %s:\n", label);
  for (size_t i = 0; i < len; i++) {
    const yai_law_artifact_io_t* a = &ios[i];
    if (!a->role) continue;
    printf("    - role=%s", a->role);
    if (a->schema_ref) printf("  schema=%s", a->schema_ref);
    if (a->path_hint) printf("  hint=%s", a->path_hint);
    printf("\n");
  }
}

static const yai_law_command_t* find_by_name_exact(const yai_law_registry_t* r, const char* name) {
  if (!r || !name) return NULL;
  for (size_t i = 0; i < r->commands_len; i++) {
    const yai_law_command_t* c = &r->commands[i];
    if (c->name && strcmp(c->name, name) == 0) return c;
  }
  return NULL;
}

int yai_law_help_print_global(void) {
  if (yai_law_registry_init() != 0) return 1;

  const yai_law_registry_t* r = yai_law_registry();
  if (!r) return 2;

  print_header("YAI CLI (registry-driven) — Help");
  printf("\n");
  printf("Usage:\n");
  printf("  yai <group> <command> [args]\n");
  printf("  yai help [group|command_id|name]\n");
  printf("\n");

  // We don’t have a group list exported; derive by scanning commands and printing in stable order.
  // Strategy: print in the order they appear in registry (already canonical).
  printf("Commands:\n");
  const char* last_group = NULL;
  for (size_t i = 0; i < r->commands_len; i++) {
    const yai_law_command_t* c = &r->commands[i];
    if (!c->group || !c->name) continue;

    if (!last_group || strcmp(last_group, c->group) != 0) {
      printf("\n%s:\n", c->group);
      last_group = c->group;
    }
    printf("  %-14s  %s\n", c->name, c->summary ? c->summary : "");
  }

  printf("\nTips:\n");
  printf("  - Use `yai help <group>` to list group commands.\n");
  printf("  - Use `yai help <yai.group.name>` to inspect one command contract.\n");
  return 0;
}

int yai_law_help_print_group(const char* group) {
  if (!group || group[0] == 0) return 1;
  if (yai_law_registry_init() != 0) return 2;

  yai_law_cmd_list_t lst = yai_law_cmds_by_group(group);
  if (!lst.items || lst.len == 0) return 3;

  printf("Group: %s\n\n", group);
  for (size_t i = 0; i < lst.len; i++) {
    const yai_law_command_t* c = lst.items[i];
    if (!c) continue;
    printf("  %-14s  %s\n", c->name ? c->name : "-", c->summary ? c->summary : "");
  }

  printf("\nUse:\n");
  printf("  yai help yai.%s.<name>\n", group);
  return 0;
}

int yai_law_help_print_command(const char* command_id) {
  if (!command_id || command_id[0] == 0) return 1;
  if (yai_law_registry_init() != 0) return 2;

  const yai_law_registry_t* r = yai_law_registry();
  const yai_law_command_t* c = yai_law_cmd_by_id(command_id);
  if (!r || !c) return 3;

  printf("%s\n\n", c->id);
  printf("  group:   %s\n", c->group ? c->group : "-");
  printf("  name:    %s\n", c->name ? c->name : "-");
  printf("  summary: %s\n", c->summary ? c->summary : "-");
  printf("\n");

  print_args(c);
  printf("\n");

  print_list_str("Outputs", c->outputs, c->outputs_len);
  print_list_str("Side effects", c->side_effects, c->side_effects_len);
  print_list_str("Law invariants", c->law_invariants, c->law_invariants_len);
  print_list_str("Law boundaries", c->law_boundaries, c->law_boundaries_len);
  print_list_str("Uses primitives", c->uses_primitives, c->uses_primitives_len);

  if (c->emits_artifacts_len || c->consumes_artifacts_len) printf("\n");
  print_art_ios(r, "Emits artifacts", c->emits_artifacts, c->emits_artifacts_len);
  print_art_ios(r, "Consumes artifacts", c->consumes_artifacts, c->consumes_artifacts_len);

  return 0;
}

int yai_law_help_print_any(const char* token) {
  if (!token || token[0] == 0) return yai_law_help_print_global();

  // 1) full id?
  if (strncmp(token, "yai.", 4) == 0) {
    return yai_law_help_print_command(token);
  }

  // 2) group?
  int rc = yai_law_help_print_group(token);
  if (rc == 0) return 0;

  // 3) name exact match
  if (yai_law_registry_init() != 0) return 2;
  const yai_law_registry_t* r = yai_law_registry();
  const yai_law_command_t* c = find_by_name_exact(r, token);
  if (c && c->id) return yai_law_help_print_command(c->id);

  return 3;
}