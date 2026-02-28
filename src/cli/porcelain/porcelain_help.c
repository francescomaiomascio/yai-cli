/* SPDX-License-Identifier: Apache-2.0 */
// src/porcelain/porcelain_help.c

#include "yai_cli/porcelain/porcelain_help.h"

#include "yai_sdk/registry/registry_registry.h"
#include "yai_cli/porcelain/porcelain_errors.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

/* =========================================================
 * Plain output helpers (no bullets, no key/value formatting)
 * ========================================================= */

static void out_line(const char *s)
{
  if (!s) s = "";
  fputs(s, stdout);
  fputc('\n', stdout);
}

static void out_blank(void)
{
  fputc('\n', stdout);
}

static void out_hr(char ch)
{
  /* consistent width, deterministic */
  char buf[80];
  memset(buf, 0, sizeof(buf));
  for (size_t i = 0; i < sizeof(buf) - 1; i++) buf[i] = ch;
  buf[sizeof(buf) - 1] = '\0';
  out_line(buf);
}

static void out_heading(const char *name)
{
  out_line(name ? name : "");
  out_hr('=');
}

static void out_heading_minor(const char *name)
{
  out_line(name ? name : "");
  out_hr('-');
}

/* =========================================================
 * Errors (consistent + actionable)
 * ========================================================= */

static int err_dep_missing(const char *detail)
{
  yai_porcelain_err_print(
    YAI_PORCELAIN_ERR_DEP_MISSING,
    detail ? detail : "dependency missing"
  );
  return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_DEP_MISSING);
}

static int err_usage(const char *detail)
{
  yai_porcelain_err_print(
    YAI_PORCELAIN_ERR_USAGE,
    detail ? detail : "invalid arguments"
  );
  return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_USAGE);
}

static int ensure_registry(void)
{
  if (yai_law_registry_init() != 0) {
    return err_dep_missing("registry unavailable (deps/yai-law unreadable or invalid)");
  }
  if (!yai_law_registry()) {
    return err_dep_missing("registry not loaded");
  }
  return 0;
}

static const yai_law_registry_t *reg_or_null(void)
{
  return yai_law_registry();
}

/* =========================================================
 * UX catalog (descriptions only; no runtime logic depends on these)
 * ========================================================= */

static const char *group_desc(const char *g)
{
  if (!g) return NULL;

  if (strcmp(g, "lifecycle") == 0) return "Start/stop stack components and sessions.";
  if (strcmp(g, "inspect") == 0)   return "Read-only diagnostics (status, logs, streams).";
  if (strcmp(g, "verify") == 0)    return "Verification and test gates.";
  if (strcmp(g, "control") == 0)   return "Control plane operations (root/kernel/providers/sessions).";
  if (strcmp(g, "memory") == 0)    return "Mind memory operations (graph, embed).";
  if (strcmp(g, "substrate") == 0) return "Deterministic primitives (hash, record, manifest, fs).";
  if (strcmp(g, "governance") == 0) return "Governance operations (policy, decision, evidence, scope).";
  if (strcmp(g, "bundle") == 0)    return "Bundle build/seal/export/import/verify.";
  if (strcmp(g, "orch") == 0)      return "Orchestration (pack, trial, runner, jobs).";

  return NULL;
}

/* These are “command sets” for presentation. */
typedef struct yai_help_set_def {
  const char *id;          /* internal label key */
  const char *title;       /* printed title */
  const char *groups[8];   /* groups included */
} yai_help_set_def_t;

static const yai_help_set_def_t g_sets[] = {
  { "runtime",     "RUNTIME LIFECYCLE",    { "lifecycle", NULL } },
  { "inspect",     "INSPECT AND DIAGNOSTICS",{ "inspect", NULL } },
  { "verify",      "VERIFICATION",         { "verify", NULL } },
  { "control",     "CONTROL PLANE",        { "control", NULL } },
  { "memory",      "MIND / MEMORY",        { "memory", NULL } },
  { "substrate",   "SUBSTRATE PRIMITIVES", { "substrate", NULL } },
  { "governance",  "GOVERNANCE",           { "governance", NULL } },
  { "bundle",      "BUNDLES",              { "bundle", NULL } },
  { "orch",        "ORCHESTRATION",        { "orch", NULL } },
};

/* =========================================================
 * Sorting helpers (stable output)
 * ========================================================= */

static int cmp_str_ptr(const void *a, const void *b)
{
  const char *sa = *(const char * const *)a;
  const char *sb = *(const char * const *)b;
  if (!sa && !sb) return 0;
  if (!sa) return -1;
  if (!sb) return 1;
  return strcmp(sa, sb);
}

static int cmp_cmd_ptr_by_name(const void *a, const void *b)
{
  const yai_law_command_t *ca = *(const yai_law_command_t * const *)a;
  const yai_law_command_t *cb = *(const yai_law_command_t * const *)b;
  const char *na = (ca && ca->name) ? ca->name : "";
  const char *nb = (cb && cb->name) ? cb->name : "";
  return strcmp(na, nb);
}

static int cmp_cmd_ptr_by_group_then_name(const void *a, const void *b)
{
  const yai_law_command_t *ca = *(const yai_law_command_t * const *)a;
  const yai_law_command_t *cb = *(const yai_law_command_t * const *)b;

  const char *ga = (ca && ca->group) ? ca->group : "";
  const char *na = (ca && ca->name)  ? ca->name  : "";
  const char *gb = (cb && cb->group) ? cb->group : "";
  const char *nb = (cb && cb->name)  ? cb->name  : "";

  int rg = strcmp(ga, gb);
  if (rg != 0) return rg;
  return strcmp(na, nb);
}

/* =========================================================
 * Alias + lookup
 *   Enterprise rule: alias = "<group>-<name>"
 * ========================================================= */

static void build_alias(const yai_law_command_t *c, char *buf, size_t cap)
{
  if (!buf || cap == 0) return;
  buf[0] = '\0';

  if (!c || !c->group || !c->name) {
    snprintf(buf, cap, "unknown");
    return;
  }
  snprintf(buf, cap, "%s-%s", c->group, c->name);
}

static const yai_law_command_t *find_command_by_alias(const yai_law_registry_t *reg, const char *alias)
{
  if (!reg || !alias || !alias[0]) return NULL;

  for (size_t i = 0; i < reg->commands_len; i++) {
    const yai_law_command_t *c = &reg->commands[i];
    if (!c || !c->group || !c->name) continue;

    char tmp[256];
    build_alias(c, tmp, sizeof(tmp));
    if (strcmp(tmp, alias) == 0) return c;
  }
  return NULL;
}

/* =========================================================
 * Group enumeration
 * ========================================================= */

static int collect_unique_groups_sorted(const yai_law_registry_t *reg, const char ***out, size_t *out_len)
{
  if (!reg || !out || !out_len) return 1;

  *out = NULL;
  *out_len = 0;

  const size_t n = reg->commands_len;
  if (n == 0) return 0;

  const char **groups = (const char **)calloc(n, sizeof(char *));
  if (!groups) return 2;

  size_t g_len = 0;

  for (size_t i = 0; i < n; i++) {
    const char *g = reg->commands[i].group;
    if (!g || !g[0]) continue;

    int seen = 0;
    for (size_t j = 0; j < g_len; j++) {
      if (groups[j] && strcmp(groups[j], g) == 0) { seen = 1; break; }
    }
    if (!seen) groups[g_len++] = g;
  }

  qsort(groups, g_len, sizeof(groups[0]), cmp_str_ptr);

  *out = groups;
  *out_len = g_len;
  return 0;
}

/* =========================================================
 * Printing utilities
 * ========================================================= */

static void print_kv_line(const char *k, const char *v)
{
  /* Manpage-like: "key: value" */
  if (!k) k = "";
  if (!v) v = "";
  char line[1024];
  snprintf(line, sizeof(line), "%s: %s", k, v);
  out_line(line);
}

static void print_cmd_line(const yai_law_command_t *c)
{
  if (!c) return;

  char alias[256];
  build_alias(c, alias, sizeof(alias));

  /* aligned command list: "  <alias>  <summary>" */
  char line[1024];
  snprintf(line, sizeof(line), "  %-22s %s", alias, (c->summary ? c->summary : ""));
  out_line(line);
}

/* =========================================================
 * Global help
 * ========================================================= */

static void print_global_usage(void)
{
  out_heading("usage: yai [global options] <command> [<args>]");
}

static void print_global_name_desc(void)
{
  out_blank();

  out_heading_minor("NAME");
  out_line("  yai - governed runtime command-line interface");

  out_blank();

  out_heading_minor("DESCRIPTION");
  out_line("  Registry-driven interface for governed runtime operations.");
  out_line("  Help output is deterministic and derived from the registry.");
}

static void print_global_synopsis(void)
{
  out_blank();

  out_heading_minor("SYNOPSIS");
  out_line("  yai <group> <command> [options]");
  out_line("  yai help [<group>|<command>|yai.<group>.<command>]");
  out_line("  yai help --all");
  out_line("  yai help --groups");
}

static void print_global_options(void)
{
  out_blank();

  out_heading_minor("GLOBAL OPTIONS");
  print_kv_line("--ws <id>",          "Workspace selector (default: config).");
  print_kv_line("--json",             "Machine-readable output (where supported).");
  print_kv_line("--timeout-ms <ms>",  "Operation timeout (where supported).");
  print_kv_line("--arming",           "Enable privileged operations (where required).");
  print_kv_line("--role <operator|system>", "Authority role (default: operator).");
  print_kv_line("-h, --help",         "Show help for the current context.");
}

static void print_global_examples(void)
{
  out_blank();

  out_heading_minor("EXAMPLES");
  out_line("  yai help");
  out_line("  yai help control");
  out_line("  yai help control-root");
  out_line("  yai help yai.control.root");
  out_line("  yai inspect status");
  out_line("  yai control root ping");
}

static int print_command_sets(const yai_law_registry_t *reg)
{
  out_blank();
  out_heading_minor("COMMON COMMANDS");

  if (!reg || reg->commands_len == 0) {
    out_line("  (no commands registered)");
    return 0;
  }

  /* We present sets in a fixed order (g_sets). Within each group, commands are name-sorted. */
  for (size_t si = 0; si < (sizeof(g_sets) / sizeof(g_sets[0])); si++) {
    const yai_help_set_def_t *set = &g_sets[si];
    if (!set->title) continue;

    /* Collect commands for all groups in this set. */
    /* Upper bound: reg->commands_len */
    yai_law_command_t **cmds = (yai_law_command_t **)calloc(reg->commands_len, sizeof(yai_law_command_t *));
    if (!cmds) return err_dep_missing("out of memory");

    size_t c_len = 0;

    for (size_t gi = 0; set->groups[gi]; gi++) {
      const char *g = set->groups[gi];

      yai_law_cmd_list_t lst = yai_law_cmds_by_group(g);
      if (!lst.items || lst.len == 0) continue;

      for (size_t i = 0; i < lst.len; i++) {
        const yai_law_command_t *c = lst.items[i];
        if (!c) continue;
        cmds[c_len++] = (yai_law_command_t *)c;
      }
    }

    if (c_len == 0) {
      free(cmds);
      continue; /* skip empty sections */
    }

    /* sort by command name for readability */
    qsort(cmds, c_len, sizeof(cmds[0]), cmp_cmd_ptr_by_name);

    out_blank();
    out_heading_minor(set->title);

    for (size_t i = 0; i < c_len; i++) {
      print_cmd_line(cmds[i]);
    }

    free(cmds);
  }

  return 0;
}

static void print_more_help(void)
{
  out_blank();

  out_heading_minor("MORE HELP");
  out_line("  yai help --all      List all available commands (aliases).");
  out_line("  yai help --groups   List available command groups.");
  out_line("  yai help <group>    List commands in a group.");
  out_line("  yai help <command>  Show detailed help for a command alias.");
  out_line("  yai help yai.<...>  Show detailed help for a canonical command id.");
}

static void print_exit_status(void)
{
  out_blank();

  out_heading_minor("EXIT STATUS");
  print_kv_line("0", "Success.");
  print_kv_line("1", "Generic failure.");
  print_kv_line("2", "Invalid arguments / contract violation.");
  print_kv_line("3", "Dependency missing (e.g. registry unavailable).");
  print_kv_line("4", "Runtime not ready.");
}

static int print_global_help(void)
{
  int rc = ensure_registry();
  if (rc != 0) return rc;

  const yai_law_registry_t *reg = reg_or_null();
  if (!reg) return err_dep_missing("registry not loaded");

  print_global_usage();
  print_global_name_desc();
  print_global_synopsis();
  print_global_options();

  rc = print_command_sets(reg);
  if (rc != 0) return rc;

  print_global_examples();
  print_more_help();
  print_exit_status();
  return 0;
}

/* =========================================================
 * --groups
 * ========================================================= */

static int print_groups_only(void)
{
  int rc = ensure_registry();
  if (rc != 0) return rc;

  const yai_law_registry_t *reg = reg_or_null();
  if (!reg) return err_dep_missing("registry not loaded");

  const char **groups = NULL;
  size_t g_len = 0;

  rc = collect_unique_groups_sorted(reg, &groups, &g_len);
  if (rc != 0) return err_dep_missing("failed to enumerate groups");

  out_heading("YAI command groups");

  if (g_len == 0) {
    out_line("  (none)");
    free(groups);
    return 0;
  }

  for (size_t i = 0; i < g_len; i++) {
    const char *g = groups[i];
    if (!g) continue;

    const char *d = group_desc(g);
    if (d) {
      char line[1024];
      snprintf(line, sizeof(line), "  %-16s %s", g, d);
      out_line(line);
    } else {
      char line[256];
      snprintf(line, sizeof(line), "  %s", g);
      out_line(line);
    }
  }

  free(groups);
  return 0;
}

/* =========================================================
 * --all
 * ========================================================= */

static int print_all_commands(void)
{
  int rc = ensure_registry();
  if (rc != 0) return rc;

  const yai_law_registry_t *reg = reg_or_null();
  if (!reg) return err_dep_missing("registry not loaded");

  out_heading("YAI commands (all)");

  if (reg->commands_len == 0) {
    out_line("  (none)");
    return 0;
  }

  yai_law_command_t **sorted = (yai_law_command_t **)calloc(reg->commands_len, sizeof(yai_law_command_t *));
  if (!sorted) return err_dep_missing("out of memory");

  for (size_t i = 0; i < reg->commands_len; i++) {
    sorted[i] = (yai_law_command_t *)&reg->commands[i];
  }
  qsort(sorted, reg->commands_len, sizeof(sorted[0]), cmp_cmd_ptr_by_group_then_name);

  out_blank();
  for (size_t i = 0; i < reg->commands_len; i++) {
    const yai_law_command_t *c = sorted[i];
    if (!c) continue;
    print_cmd_line(c);
  }

  out_blank();
  out_heading_minor("NOTES");
  out_line("  Alias format is deterministic: <group>-<name>.");
  out_line("  Use 'yai help <command>' for detailed help.");
  out_line("  Use 'yai help yai.<group>.<name>' to reference a canonical command id.");

  free(sorted);
  return 0;
}

/* =========================================================
 * Group help
 * ========================================================= */

static int print_group_help(const char *group)
{
  if (!group || !group[0]) return err_usage("missing group");

  int rc = ensure_registry();
  if (rc != 0) return rc;

  yai_law_cmd_list_t lst = yai_law_cmds_by_group(group);
  if (!lst.items || lst.len == 0) {
    return err_usage("unknown group (try: yai help --groups)");
  }

  out_heading("YAI help (group)");

  out_blank();
  out_heading_minor("GROUP");
  {
    const char *d = group_desc(group);
    if (d) {
      char line[1024];
      snprintf(line, sizeof(line), "  %s - %s", group, d);
      out_line(line);
    } else {
      char line[256];
      snprintf(line, sizeof(line), "  %s", group);
      out_line(line);
    }
  }

  out_blank();
  out_heading_minor("COMMANDS");

  yai_law_command_t **sorted = (yai_law_command_t **)calloc(lst.len, sizeof(yai_law_command_t *));
  if (!sorted) return err_dep_missing("out of memory");

  for (size_t i = 0; i < lst.len; i++) sorted[i] = (yai_law_command_t *)lst.items[i];
  qsort(sorted, lst.len, sizeof(sorted[0]), cmp_cmd_ptr_by_name);

  for (size_t i = 0; i < lst.len; i++) {
    const yai_law_command_t *c = sorted[i];
    if (!c) continue;
    print_cmd_line(c);
  }

  out_blank();
  out_heading_minor("SEE ALSO");
  out_line("  yai help");
  out_line("  yai help --all");

  free(sorted);
  return 0;
}

/* =========================================================
 * Command help (contract-level, clean)
 * ========================================================= */

static int is_flag_arg(const yai_law_arg_t *a)
{
  return (a && a->flag && a->flag[0] != '\0');
}

static int is_pos_arg(const yai_law_arg_t *a)
{
  return (a && a->pos > 0);
}

static void print_values_inline(const yai_law_arg_t *a)
{
  if (!a || !a->values || a->values_len == 0) return;

  out_line("    values:");
  for (size_t i = 0; i < a->values_len; i++) {
    if (!a->values[i]) continue;
    char line[512];
    snprintf(line, sizeof(line), "      - %s", a->values[i]);
    out_line(line);
  }
}

static void build_synopsis(const yai_law_command_t *c, char *buf, size_t cap)
{
  if (!buf || cap == 0) return;
  buf[0] = '\0';

  if (!c) {
    snprintf(buf, cap, "yai <command> [<args>]");
    return;
  }

  char alias[256];
  build_alias(c, alias, sizeof(alias));

  size_t off = 0;
  off += (size_t)snprintf(buf + off, cap - off, "yai %s", alias);

  /* required positional args */
  if (c->args && c->args_len > 0) {
    for (size_t i = 0; i < c->args_len; i++) {
      const yai_law_arg_t *a = &c->args[i];
      if (!a || !a->name) continue;
      if (a->required && is_pos_arg(a)) {
        off += (size_t)snprintf(buf + off, cap - off, " <%s>", a->name);
      }
    }
  }

  /* add [options] if any flags exist */
  int has_flags = 0;
  if (c->args && c->args_len > 0) {
    for (size_t i = 0; i < c->args_len; i++) {
      if (is_flag_arg(&c->args[i])) { has_flags = 1; break; }
    }
  }
  if (has_flags) {
    off += (size_t)snprintf(buf + off, cap - off, " [options]");
  }
}

static void print_arg_line(const yai_law_arg_t *a)
{
  if (!a || !a->name) return;

  char left[256];
  left[0] = '\0';

  if (is_flag_arg(a)) {
    if (a->type && strcmp(a->type, "bool") == 0) {
      snprintf(left, sizeof(left), "%s", a->flag);
    } else if (a->type) {
      snprintf(left, sizeof(left), "%s <%s>", a->flag, a->type);
    } else {
      snprintf(left, sizeof(left), "%s <value>", a->flag);
    }
  } else {
    if (a->type) snprintf(left, sizeof(left), "%s <%s>", a->name, a->type);
    else snprintf(left, sizeof(left), "%s <value>", a->name);
  }

  char meta[256];
  meta[0] = '\0';
  snprintf(meta, sizeof(meta), "%s", a->required ? "required" : "optional");

  if (a->default_b_set) {
    char tmp[64];
    snprintf(tmp, sizeof(tmp), ", default=%s", a->default_b ? "true" : "false");
    strncat(meta, tmp, sizeof(meta) - strlen(meta) - 1);
  } else if (a->default_i_set) {
    char tmp[96];
    snprintf(tmp, sizeof(tmp), ", default=%" PRId64, (int64_t)a->default_i);
    strncat(meta, tmp, sizeof(meta) - strlen(meta) - 1);
  } else if (a->default_s) {
    strncat(meta, ", default=", sizeof(meta) - strlen(meta) - 1);
    strncat(meta, a->default_s, sizeof(meta) - strlen(meta) - 1);
  }

  char line[1024];
  snprintf(line, sizeof(line), "  %-28s %s", left, meta);
  out_line(line);

  print_values_inline(a);
}

static void print_str_list(const char *title, const char * const *items, size_t len)
{
  if (!items || len == 0) return;
  out_blank();
  out_heading_minor(title);
  for (size_t i = 0; i < len; i++) {
    if (!items[i]) continue;
    char line[512];
    snprintf(line, sizeof(line), "  - %s", items[i]);
    out_line(line);
  }
}

static void print_artifacts_io(const char *title, const yai_law_artifact_io_t *items, size_t len)
{
  if (!items || len == 0) return;

  out_blank();
  out_heading_minor(title);

  for (size_t i = 0; i < len; i++) {
    const yai_law_artifact_io_t *io = &items[i];
    if (!io || !io->role) continue;

    char line[512];
    snprintf(line, sizeof(line), "  - %s", io->role);
    out_line(line);

    if (io->schema_ref) {
      char l2[1024];
      snprintf(l2, sizeof(l2), "      schema: %s", io->schema_ref);
      out_line(l2);
    }
    if (io->path_hint) {
      char l3[1024];
      snprintf(l3, sizeof(l3), "      path_hint: %s", io->path_hint);
      out_line(l3);
    }
  }
}

static int print_command_help_by_ptr(const yai_law_command_t *c)
{
  if (!c) return err_usage("unknown command (try: yai help --all)");

  char alias[256];
  build_alias(c, alias, sizeof(alias));

  out_heading("YAI help (command)");

  out_blank();
  out_heading_minor("COMMAND");
  {
    char line[1024];
    snprintf(line, sizeof(line), "  %s", alias);
    out_line(line);
  }
  if (c->summary) {
    char line[1024];
    snprintf(line, sizeof(line), "  summary: %s", c->summary);
    out_line(line);
  }
  if (c->id) {
    char line[1024];
    snprintf(line, sizeof(line), "  canonical_id: %s", c->id);
    out_line(line);
  }

  out_blank();
  out_heading_minor("SYNOPSIS");
  {
    char syn[1024];
    build_synopsis(c, syn, sizeof(syn));
    out_line("  ");
    out_line("  ");
    /* keep it readable */
    {
      char sline[1100];
      snprintf(sline, sizeof(sline), "  %s", syn);
      out_line(sline);
    }
  }

  out_blank();
  out_heading_minor("OPTIONS");
  {
    int any = 0;
    if (c->args && c->args_len > 0) {
      for (size_t i = 0; i < c->args_len; i++) {
        const yai_law_arg_t *a = &c->args[i];
        if (!is_flag_arg(a)) continue;
        any = 1;
        print_arg_line(a);
      }
    }
    if (!any) out_line("  (none)");
  }

  out_blank();
  out_heading_minor("ARGUMENTS");
  {
    int any = 0;
    if (c->args && c->args_len > 0) {
      for (size_t i = 0; i < c->args_len; i++) {
        const yai_law_arg_t *a = &c->args[i];
        if (!is_pos_arg(a)) continue;
        any = 1;
        print_arg_line(a);
      }
    }
    if (!any) out_line("  (none)");
  }

  /* Contract metadata (kept structured, not noisy) */
  print_str_list("OUTPUTS", c->outputs, c->outputs_len);
  print_str_list("SIDE EFFECTS", c->side_effects, c->side_effects_len);
  print_str_list("CONTRACT HOOKS", c->law_hooks, c->law_hooks_len);
  print_str_list("CONTRACT INVARIANTS", c->law_invariants, c->law_invariants_len);
  print_str_list("CONTRACT BOUNDARIES", c->law_boundaries, c->law_boundaries_len);
  print_str_list("USES PRIMITIVES", c->uses_primitives, c->uses_primitives_len);
  print_artifacts_io("EMITS ARTIFACTS", c->emits_artifacts, c->emits_artifacts_len);
  print_artifacts_io("CONSUMES ARTIFACTS", c->consumes_artifacts, c->consumes_artifacts_len);

  out_blank();
  out_heading_minor("SEE ALSO");
  out_line("  yai help");
  out_line("  yai help --all");
  if (c->group) {
    char sa[256];
    snprintf(sa, sizeof(sa), "  yai help %s", c->group);
    out_line(sa);
  }

  return 0;
}

static int print_command_help_token(const char *token)
{
  if (!token || !token[0]) return err_usage("missing command");

  int rc = ensure_registry();
  if (rc != 0) return rc;

  const yai_law_registry_t *reg = reg_or_null();
  if (!reg) return err_dep_missing("registry not loaded");

  /* canonical id: yai.<group>.<name> */
  if (strncmp(token, "yai.", 4) == 0) {
    const yai_law_command_t *c = yai_law_cmd_by_id(token);
    if (!c) return err_usage("unknown canonical command id (try: yai help --all)");
    return print_command_help_by_ptr(c);
  }

  /* alias: <group>-<name> */
  const yai_law_command_t *c = find_command_by_alias(reg, token);
  if (!c) return err_usage("unknown command (try: yai help --all)");
  return print_command_help_by_ptr(c);
}

/* =========================================================
 * Entry point
 * ========================================================= */

int yai_porcelain_help_print_any(const char *token)
{
  /* No token => global help */
  if (!token || token[0] == '\0') return print_global_help();

  /* Flags */
  if (strcmp(token, "-a") == 0 || strcmp(token, "--all") == 0) return print_all_commands();
  if (strcmp(token, "-g") == 0 || strcmp(token, "--groups") == 0) return print_groups_only();

  /* Group name? Keep legacy behavior: "yai help <group>" */
  {
    int rc = ensure_registry();
    if (rc != 0) return rc;

    yai_law_cmd_list_t lst = yai_law_cmds_by_group(token);
    if (lst.items && lst.len > 0) {
      return print_group_help(token);
    }
  }

  /* Otherwise treat as command token:
     - alias: <group>-<name>
     - or canonical id: yai.<group>.<name>
  */
  return print_command_help_token(token);
}