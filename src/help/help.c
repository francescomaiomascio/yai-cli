/* SPDX-License-Identifier: Apache-2.0 */

#include "yai_cli/help.h"

#include "yai_cli/errors.h"
#include "yai_cli/pager.h"
#include "yai_sdk/registry/command_catalog.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

typedef struct {
  char *buf;
  size_t len;
  size_t cap;
} strbuf_t;

static int sb_reserve(strbuf_t *sb, size_t need)
{
  char *nb;
  size_t ncap;
  if (!sb) return 1;
  if (sb->len + need + 1 <= sb->cap) return 0;
  ncap = (sb->cap == 0) ? 1024 : sb->cap * 2;
  while (ncap < sb->len + need + 1) ncap *= 2;
  nb = (char *)realloc(sb->buf, ncap);
  if (!nb) return 1;
  sb->buf = nb;
  sb->cap = ncap;
  return 0;
}

static int sb_appendf(strbuf_t *sb, const char *fmt, ...)
{
  va_list ap;
  va_list ap2;
  int n;
  if (!sb || !fmt) return 1;
  va_start(ap, fmt);
  va_copy(ap2, ap);
  n = vsnprintf(NULL, 0, fmt, ap);
  va_end(ap);
  if (n < 0) { va_end(ap2); return 1; }
  if (sb_reserve(sb, (size_t)n) != 0) { va_end(ap2); return 1; }
  vsnprintf(sb->buf + sb->len, sb->cap - sb->len, fmt, ap2);
  sb->len += (size_t)n;
  va_end(ap2);
  return 0;
}

static void sb_free(strbuf_t *sb)
{
  if (!sb) return;
  free(sb->buf);
  sb->buf = NULL;
  sb->len = 0;
  sb->cap = 0;
}

static int help_error(const char *msg, const char *hint)
{
  fprintf(stderr, "help\n");
  fprintf(stderr, "BAD ARGS\n");
  fprintf(stderr, "%s\n", msg ? msg : "invalid help input");
  if (hint && hint[0]) fprintf(stderr, "Hint: %s\n", hint);
  return 20;
}

static const char *map_entrypoint(const char *group)
{
  if (!group) return "run";
  if (strcmp(group, "governance") == 0) return "gov";
  if (strcmp(group, "verify") == 0) return "verify";
  if (strcmp(group, "inspect") == 0) return "inspect";
  if (strcmp(group, "bundle") == 0) return "bundle";
  if (strcmp(group, "kernel") == 0) return "ws";
  if (strcmp(group, "lifecycle") == 0) return "run";
  if (strcmp(group, "control") == 0) return "run";
  if (strcmp(group, "root") == 0 || strcmp(group, "boot") == 0 || strcmp(group, "engine") == 0 ||
      strcmp(group, "mind") == 0 || strcmp(group, "memory") == 0 || strcmp(group, "substrate") == 0 || strcmp(group, "orch") == 0) return "run";
  return "config";
}

static void split_name_topic_op(const char *name, const char **topic, const char **op)
{
  static char t[64];
  static char o[64];
  const char *u;
  if (!name || !name[0]) { *topic = "general"; *op = "run"; return; }
  u = strchr(name, '_');
  if (!u) { *topic = "general"; *op = name; return; }
  {
    size_t tn = (size_t)(u - name);
    size_t on = strlen(u + 1);
    if (tn >= sizeof(t)) tn = sizeof(t) - 1;
    if (on >= sizeof(o)) on = sizeof(o) - 1;
    memcpy(t, name, tn); t[tn] = '\0';
    memcpy(o, u + 1, on); o[on] = '\0';
    *topic = t;
    *op = o;
  }
}

static int print_version(void)
{
  FILE *f = fopen("VERSION", "r");
  if (!f) { puts("yai-cli (version unknown)"); return 0; }
  {
    char buf[128];
    if (fgets(buf, sizeof(buf), f)) {
      size_t n = strlen(buf);
      while (n && (buf[n - 1] == '\n' || buf[n - 1] == '\r')) { buf[n - 1] = '\0'; n--; }
      printf("yai-cli %s\n", buf);
    } else {
      puts("yai-cli (version unknown)");
    }
  }
  fclose(f);
  return 0;
}

static int render_global_help(const yai_sdk_command_catalog_t *idx, strbuf_t *sb, int all)
{
  (void)idx;
  sb_appendf(sb, "YAI Operator CLI\n\n");
  sb_appendf(sb, "Usage:\n");
  sb_appendf(sb, "  yai <entrypoint> <topic> [op] [options]\n");
  sb_appendf(sb, "  yai help <entrypoint> [topic] [op]\n\n");
  sb_appendf(sb, "Main Operator Commands:\n");
  sb_appendf(sb, "  ws           workspace lifecycle\n");
  sb_appendf(sb, "  run          runtime execution and control\n");
  sb_appendf(sb, "  gov          governance operations\n");
  sb_appendf(sb, "  verify       verification and proofs\n");
  sb_appendf(sb, "  inspect      read-only introspection\n");
  sb_appendf(sb, "  bundle       bundle operations\n");
  sb_appendf(sb, "  config       configuration\n");
  sb_appendf(sb, "  doctor       diagnostics\n");
  sb_appendf(sb, "  watch        watch mode\n");
  sb_appendf(sb, "  help         help and references\n");
  sb_appendf(sb, "  version      version information\n");
  if (all) {
    sb_appendf(sb, "\nInternal Commands:\n");
    sb_appendf(sb, "  root/kernel/boot/engine/mind/substrate/orch/lifecycle/memory/control (legacy groups)\n");
  }
  return 0;
}

static int render_entrypoint_help(const yai_sdk_command_catalog_t *idx, const char *entrypoint, strbuf_t *sb)
{
  int found = 0;
  sb_appendf(sb, "%s\n\n", entrypoint);
  sb_appendf(sb, "Topics:\n");
  for (size_t i = 0; i < idx->group_count; i++) {
    const yai_sdk_command_group_t *g = &idx->groups[i];
    const char *ep = map_entrypoint(g->group);
    if (strcmp(ep, entrypoint) != 0) continue;
    sb_appendf(sb, "  %-18s %s\n", g->group, "registry topic");
    found = 1;
  }
  if (!found) return help_error("unknown entrypoint", "Run: yai help");
  return 0;
}

static int render_topic_help(const yai_sdk_command_catalog_t *idx, const char *entrypoint, const char *topic, strbuf_t *sb)
{
  const yai_sdk_command_group_t *g = yai_sdk_command_catalog_find_group(idx, topic);
  if (!g || strcmp(map_entrypoint(g->group), entrypoint) != 0) {
    return help_error("unknown topic", "Run: yai help <entrypoint>");
  }
  sb_appendf(sb, "%s %s\n\n", entrypoint, topic);
  sb_appendf(sb, "Operations:\n");
  for (size_t j = 0; j < g->command_count; j++) {
    const char *t = NULL;
    const char *op = NULL;
    split_name_topic_op(g->commands[j].name, &t, &op);
    if (strcmp(t, topic) == 0 || strcmp(t, "general") == 0) {
      sb_appendf(sb, "  %-20s %s\n", op, g->commands[j].summary);
    } else {
      sb_appendf(sb, "  %-20s %s\n", g->commands[j].name, g->commands[j].summary);
    }
  }
  return 0;
}

static int render_command_help(const yai_sdk_command_ref_t *c, strbuf_t *sb)
{
  const char *topic = NULL;
  const char *op = NULL;
  const char *ep;
  if (!c) return help_error("unknown command", "Run: yai help");
  ep = map_entrypoint(c->group);
  split_name_topic_op(c->name, &topic, &op);
  sb_appendf(sb, "Command:\n");
  sb_appendf(sb, "  %s %s %s\n\n", ep, c->group, c->name);
  sb_appendf(sb, "Description:\n");
  sb_appendf(sb, "  %s\n\n", c->summary);
  sb_appendf(sb, "Usage:\n");
  sb_appendf(sb, "  yai %s %s %s\n", ep, topic, op);
  sb_appendf(sb, "  legacy: yai %s %s\n\n", c->group, c->name);
  sb_appendf(sb, "Metadata:\n");
  sb_appendf(sb, "  canonical_id: %s\n", c->id);
  return 0;
}

int yai_porcelain_help_print(const char *token1, const char *token2, const char *token3, int pager, int no_pager)
{
  yai_sdk_command_catalog_t idx;
  strbuf_t sb = {0};
  int rc;

  if (token1 && strcmp(token1, "version") == 0) return print_version();

  rc = yai_sdk_command_catalog_load(&idx);
  if (rc != 0) {
    yai_porcelain_err_print(YAI_PORCELAIN_ERR_DEP_MISSING, "registry unavailable (deps/yai-law unreadable or invalid)");
    return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_DEP_MISSING);
  }

  if (!token1 || !token1[0]) {
    rc = render_global_help(&idx, &sb, 0);
  } else if (strcmp(token1, "--all") == 0 || strcmp(token1, "-a") == 0) {
    rc = render_global_help(&idx, &sb, 1);
  } else if (strcmp(token1, "--groups") == 0 || strcmp(token1, "-g") == 0 || strcmp(token1, "topics") == 0) {
    rc = render_global_help(&idx, &sb, 0);
  } else if (strncmp(token1, "yai.", 4) == 0) {
    rc = render_command_help(yai_sdk_command_catalog_find_by_id(&idx, token1), &sb);
  } else if (token2 && token2[0] && token3 && token3[0]) {
    const yai_sdk_command_group_t *g = yai_sdk_command_catalog_find_group(&idx, token2);
    const yai_sdk_command_ref_t *c = g ? yai_sdk_command_catalog_find_command(&idx, token2, token3) : NULL;
    rc = render_command_help(c, &sb);
  } else if (token2 && token2[0]) {
    rc = render_topic_help(&idx, token1, token2, &sb);
  } else {
    rc = render_entrypoint_help(&idx, token1, &sb);
  }

  if (rc == 0 && sb.buf) yai_cli_page_if_needed(sb.buf, pager, no_pager);
  sb_free(&sb);
  yai_sdk_command_catalog_free(&idx);
  return rc;
}

int yai_porcelain_help_print_any(const char *token)
{
  return yai_porcelain_help_print(token, NULL, NULL, 0, 0);
}
