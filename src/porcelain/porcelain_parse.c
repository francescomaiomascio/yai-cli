/* SPDX-License-Identifier: Apache-2.0 */
// src/porcelain/porcelain_parse.c

#include "yai_cli/porcelain/porcelain_parse.h"
#include "yai_cli/law/law_registry.h"

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

  /* `yai --help` / `yai -h` */
  if (is_help_token(argv[1])) {
    req->kind = YAI_PORCELAIN_KIND_HELP;
    req->help_token = (argc >= 3) ? argv[2] : NULL;
    return 0;
  }

  /* `yai --version` / `yai version` */
  if (is_version_token(argv[1])) {
    req->kind = YAI_PORCELAIN_KIND_HELP;
    req->help_token = "version";
    return 0;
  }

  /* `yai law ...` */
  if (strcmp(argv[1], "law") == 0) {
    req->kind = YAI_PORCELAIN_KIND_LAW;
    req->law_argc = (argc >= 2) ? (argc - 2) : 0;
    req->law_argv = (argc >= 2) ? &argv[2] : NULL;
    return 0;
  }

  /* `yai help ...` */
  if (strcmp(argv[1], "help") == 0) {
    req->kind = YAI_PORCELAIN_KIND_HELP;
    req->help_token = (argc >= 3) ? argv[2] : NULL;
    return 0;
  }

  /* `yai <group> <name> ...` needs at least 3 tokens */
  if (argc < 3) {
    return set_err(req, "missing command name (expected: yai <group> <name>)");
  }

  const char* group = argv[1];
  const char* name  = argv[2];

  /* `yai <group> help` -> group help */
  if (is_help_token(name)) {
    req->kind = YAI_PORCELAIN_KIND_HELP;
    req->help_token = group;
    return 0;
  }

  /* resolve canonical id through registry */
  if (yai_law_registry_init() != 0) {
    return set_err(req, "law registry unavailable (deps/yai-law not readable or invalid)");
  }

  const yai_law_registry_t* reg = yai_law_registry();
  if (!reg) {
    return set_err(req, "law registry not loaded");
  }

  const yai_law_command_t* cmd = find_by_group_name(reg, group, name);
  if (!cmd || !cmd->id) {
    yai_law_cmd_list_t lst = yai_law_cmds_by_group(group);
    if (lst.items && lst.len > 0) {
      return set_err(req, "unknown command name for group (try: yai help <group>)");
    }
    return set_err(req, "unknown command group (try: yai help)");
  }

  req->kind = YAI_PORCELAIN_KIND_COMMAND;
  req->command_id = cmd->id;
  req->cmd_argc = argc - 3;
  req->cmd_argv = &argv[3];
  return 0;
}