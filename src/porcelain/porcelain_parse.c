/* SPDX-License-Identifier: Apache-2.0 */
// src/porcelain/porcelain_parse.c

#include "yai_cli/porcelain/porcelain_parse.h"
#include "yai_sdk/registry/registry_registry.h"

#include <string.h>
#include <stddef.h>

static void req_zero(yai_porcelain_request_t* r) {
  memset(r, 0, sizeof(*r));
  r->kind = YAI_PORCELAIN_KIND_NONE;
}

static int set_err(yai_porcelain_request_t* r, const char* msg) {
  r->kind = YAI_PORCELAIN_KIND_ERROR;
  r->error = msg ? msg : "unknown error";
  return 1;
}

static int is_help_token(const char* s) {
  return s && (strcmp(s, "help") == 0 || strcmp(s, "--help") == 0 || strcmp(s, "-h") == 0);
}

static int is_version_token(const char* s) {
  return s && (strcmp(s, "--version") == 0 || strcmp(s, "-V") == 0 || strcmp(s, "version") == 0);
}

/* Global options are accepted before the command and are forwarded to the command argv.
   This parser only locates the command boundary deterministically. */
static int is_global_option(const char* s) {
  if (!s || s[0] != '-') return 0;
  return (
    strcmp(s, "--ws") == 0 ||
    strcmp(s, "--json") == 0 ||
    strcmp(s, "--timeout-ms") == 0 ||
    strcmp(s, "--arming") == 0 ||
    strcmp(s, "--role") == 0 ||
    strcmp(s, "-h") == 0 || strcmp(s, "--help") == 0 ||
    strcmp(s, "--version") == 0 ||
    strcmp(s, "-V") == 0
  );
}

static int global_option_takes_value(const char* s) {
  if (!s) return 0;
  return (
    strcmp(s, "--ws") == 0 ||
    strcmp(s, "--timeout-ms") == 0 ||
    strcmp(s, "--role") == 0
  );
}

/* Group abbreviations (UX layer). */
static const char* expand_group_alias(const char* g) {
  if (!g) return NULL;

  if (strcmp(g, "gov") == 0) return "governance";
  if (strcmp(g, "sub") == 0) return "substrate";
  if (strcmp(g, "ctl") == 0) return "control";
  if (strcmp(g, "ins") == 0) return "inspect";
  if (strcmp(g, "lif") == 0) return "lifecycle";
  if (strcmp(g, "mem") == 0) return "memory";
  if (strcmp(g, "bun") == 0) return "bundle";
  if (strcmp(g, "orc") == 0) return "orch";

  return g;
}

static const yai_law_command_t*
find_by_group_name(const yai_law_registry_t* reg, const char* group, const char* name) {
  if (!reg || !group || !name) return NULL;
  for (size_t i = 0; i < reg->commands_len; i++) {
    const yai_law_command_t* c = &reg->commands[i];
    if (!c->group || !c->name || !c->id) continue;
    if (strcmp(c->group, group) == 0 && strcmp(c->name, name) == 0) return c;
  }
  return NULL;
}

/* Resolve "<group>-<name>" (alias) into a command. */
static const yai_law_command_t*
find_by_alias(const yai_law_registry_t* reg, const char* token, const char** out_group, const char** out_name) {
  if (out_group) *out_group = NULL;
  if (out_name)  *out_name  = NULL;
  if (!reg || !token || !token[0]) return NULL;

  /* must be non-flag and contain a '-' */
  if (token[0] == '-') return NULL;
  const char* dash = strchr(token, '-');
  if (!dash) return NULL;
  if (dash == token) return NULL;
  if (!dash[1]) return NULL;

  /* split without allocating: compare by temporary buffers */
  char gbuf[128];
  char nbuf[128];

  size_t glen = (size_t)(dash - token);
  size_t nlen = strlen(dash + 1);

  if (glen >= sizeof(gbuf) || nlen >= sizeof(nbuf)) return NULL;

  memcpy(gbuf, token, glen);
  gbuf[glen] = '\0';
  memcpy(nbuf, dash + 1, nlen);
  nbuf[nlen] = '\0';

  const char* g = expand_group_alias(gbuf);
  const char* n = nbuf;

  const yai_law_command_t* c = find_by_group_name(reg, g, n);
  if (c) {
    if (out_group) *out_group = c->group;
    if (out_name)  *out_name  = c->name;
  }
  return c;
}

/* Compute the index where the command token starts (after global options). */
static int find_command_start(int argc, char** argv) {
  int i = 1;
  while (i < argc && argv && argv[i]) {
    const char* t = argv[i];

    /* stop at first non-option */
    if (!is_global_option(t)) break;

    /* help/version handled outside; do not treat as value-taking globals */
    if (strcmp(t, "--help") == 0 || strcmp(t, "-h") == 0 || strcmp(t, "--version") == 0 || strcmp(t, "-V") == 0) {
      break; /* command token starts here */
    }

    if (global_option_takes_value(t)) {
      if (i + 1 >= argc) return -1; /* missing value */
      i += 2;
      continue;
    }

    i += 1;
  }
  return i;
}

int yai_porcelain_parse_argv(int argc, char** argv, yai_porcelain_request_t* req) {
  if (!req) return 1;
  req_zero(req);

  if (argc <= 0 || !argv || !argv[0]) {
    return set_err(req, "invalid argv");
  }

  /* `yai` -> show global help */
  if (argc == 1) {
    req->kind = YAI_PORCELAIN_KIND_HELP;
    req->help_token = NULL;
    return 0;
  }


  /* Early global flags: support `yai --help/-h` and `yai --version/-V` even before option scanning. */
  if (is_help_token(argv[1])) {
    req->kind = YAI_PORCELAIN_KIND_HELP;
    req->help_token = (2 < argc) ? argv[2] : NULL;
    return 0;
  }

  if (is_version_token(argv[1])) {
    req->kind = YAI_PORCELAIN_KIND_HELP;
    req->help_token = "version";
    return 0;
  }

  /* Determine where the command starts, allowing global options before it. */
  int cmdi = find_command_start(argc, argv);
  if (cmdi < 0 || cmdi >= argc || !argv[cmdi]) {
    return set_err(req, "invalid global options (missing value)");
  }

  /* `yai --help` / `yai -h` (even with global options before) */
  if (is_help_token(argv[cmdi])) {
    req->kind = YAI_PORCELAIN_KIND_HELP;
    req->help_token = (cmdi + 1 < argc) ? argv[cmdi + 1] : NULL;
    return 0;
  }

  /* `yai --version` / `yai version` (even with global options before) */
  if (is_version_token(argv[cmdi])) {
    req->kind = YAI_PORCELAIN_KIND_HELP;
    req->help_token = "version";
    return 0;
  }

  /* `yai law ...` */
  if (strcmp(argv[cmdi], "law") == 0) {
    req->kind = YAI_PORCELAIN_KIND_LAW;
    req->law_argc = (argc > cmdi + 1) ? (argc - (cmdi + 1)) : 0;
    req->law_argv = (argc > cmdi + 1) ? &argv[cmdi + 1] : NULL;
    return 0;
  }

  /* `yai help ...` */
  if (strcmp(argv[cmdi], "help") == 0) {
    req->kind = YAI_PORCELAIN_KIND_HELP;
    req->help_token = (cmdi + 1 < argc) ? argv[cmdi + 1] : NULL;
    return 0;
  }

  /* From here on, we need the registry to resolve commands. */
  if (yai_law_registry_init() != 0) {
    return set_err(req, "registry unavailable (deps/yai-law not readable or invalid)");
  }

  const yai_law_registry_t* reg = yai_law_registry();
  if (!reg) {
    return set_err(req, "registry not loaded");
  }

  /* Support alias invocation:
     `yai <group>-<name> ...` (e.g. `yai gov-policy ...` or `yai substrate-manifest ...`) */
  {
    const yai_law_command_t* c_alias = find_by_alias(reg, argv[cmdi], NULL, NULL);
    if (c_alias && c_alias->id) {
      req->kind = YAI_PORCELAIN_KIND_COMMAND;
      req->command_id = c_alias->id;
      req->cmd_argc = argc - (cmdi + 1);
      req->cmd_argv = &argv[cmdi + 1];
      return 0;
    }
  }

  /* Primary form: `yai <group> <name> ...` requires at least 2 tokens from cmdi. */
  if (cmdi + 1 >= argc || !argv[cmdi + 1]) {
    return set_err(req, "missing command name (expected: yai <group> <name>)");
  }

  const char* group_raw = argv[cmdi];
  const char* name      = argv[cmdi + 1];

  /* `yai <group> help` -> group help (even with abbreviations) */
  if (is_help_token(name)) {
    req->kind = YAI_PORCELAIN_KIND_HELP;
    req->help_token = group_raw;
    return 0;
  }

  const char* group = expand_group_alias(group_raw);

  const yai_law_command_t* cmd = find_by_group_name(reg, group, name);
  if (!cmd || !cmd->id) {
    yai_law_cmd_list_t lst = yai_law_cmds_by_group(group);
    if (lst.items && lst.len > 0) {
      return set_err(req, "unknown command name for group (try: yai help <group>)");
    }
    return set_err(req, "unknown command group (try: yai help --groups)");
  }

  req->kind = YAI_PORCELAIN_KIND_COMMAND;
  req->command_id = cmd->id;

  /* Forward remaining argv to porcelain/ops (includes any global options already consumed by caller, if needed). */
  req->cmd_argc = argc - (cmdi + 2);
  req->cmd_argv = &argv[cmdi + 2];
  return 0;
}