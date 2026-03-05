/* SPDX-License-Identifier: Apache-2.0 */

#include "yai_cli/porcelain/porcelain_help.h"

#include "yai_cli/porcelain/porcelain_errors.h"
#include "yai_cli/util/pager.h"
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
  if (n < 0) {
    va_end(ap2);
    return 1;
  }
  if (sb_reserve(sb, (size_t)n) != 0) {
    va_end(ap2);
    return 1;
  }
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

static const char *group_desc(const char *g)
{
  if (!g) return "";
  if (strcmp(g, "root") == 0) return "Runtime control plane";
  if (strcmp(g, "kernel") == 0) return "Workspace and execution";
  if (strcmp(g, "boot") == 0) return "System boot operations";
  if (strcmp(g, "engine") == 0) return "Execution engine";
  if (strcmp(g, "mind") == 0) return "Cognitive layer (future)";
  return "Registry command group";
}

static int print_version(void)
{
  FILE *f = fopen("VERSION", "r");
  if (!f) {
    puts("yai-cli (version unknown)");
    return 0;
  }
  {
    char buf[128];
    if (fgets(buf, sizeof(buf), f)) {
      size_t n = strlen(buf);
      while (n && (buf[n - 1] == '\n' || buf[n - 1] == '\r')) {
        buf[n - 1] = '\0';
        n--;
      }
      printf("yai-cli %s\n", buf);
    } else {
      puts("yai-cli (version unknown)");
    }
  }
  fclose(f);
  return 0;
}

static int help_error(const char *msg, const char *hint)
{
  yai_porcelain_err_print(YAI_PORCELAIN_ERR_USAGE, msg ? msg : "invalid help input");
  if (hint && hint[0]) yai_porcelain_err_print(YAI_PORCELAIN_ERR_USAGE, hint);
  return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_USAGE);
}

static void render_group_lines(const yai_sdk_command_catalog_t *idx, strbuf_t *sb)
{
  for (size_t i = 0; i < idx->group_count; i++) {
    const yai_sdk_command_group_t *g = &idx->groups[i];
    sb_appendf(sb, "  %-12s %s\n", g->group, group_desc(g->group));
  }
}

static int render_global_help(const yai_sdk_command_catalog_t *idx, strbuf_t *sb)
{
  sb_appendf(sb, "YAI Operator CLI\n\n");
  sb_appendf(sb, "Usage:\n");
  sb_appendf(sb, "  yai <group> <command> [options]\n");
  sb_appendf(sb, "  yai help <group>\n");
  sb_appendf(sb, "  yai help <group> <command>\n\n");
  sb_appendf(sb, "Command Groups:\n");
  render_group_lines(idx, sb);
  sb_appendf(sb, "\nRun 'yai help <group>' for more details.\n");
  return 0;
}

static int render_group_help(const yai_sdk_command_group_t *g, strbuf_t *sb)
{
  if (!g) return help_error("unknown group", "try: yai help --groups");
  sb_appendf(sb, "%s\n\n", g->group);
  sb_appendf(sb, "%s\n\n", group_desc(g->group));
  sb_appendf(sb, "Commands:\n");
  for (size_t i = 0; i < g->command_count; i++) {
    sb_appendf(sb, "  %-22s %s\n", g->commands[i].name, g->commands[i].summary);
  }
  return 0;
}

static int render_command_help(const yai_sdk_command_ref_t *c, strbuf_t *sb)
{
  if (!c) return help_error("unknown command", "try: yai help <group>");
  sb_appendf(sb, "Command:\n");
  sb_appendf(sb, "  %s %s\n\n", c->group, c->name);
  sb_appendf(sb, "Description:\n");
  sb_appendf(sb, "  %s\n\n", c->summary);
  sb_appendf(sb, "Usage:\n");
  sb_appendf(sb, "  yai %s %s\n", c->group, c->name);
  sb_appendf(sb, "  canonical_id: %s\n", c->id);
  return 0;
}

int yai_porcelain_help_print(const char *token1, const char *token2, int pager, int no_pager)
{
  yai_sdk_command_catalog_t idx;
  strbuf_t sb = {0};
  int rc;

  if (token1 && strcmp(token1, "version") == 0) {
    return print_version();
  }

  rc = yai_sdk_command_catalog_load(&idx);
  if (rc != 0) {
    yai_porcelain_err_print(YAI_PORCELAIN_ERR_DEP_MISSING, "registry unavailable (deps/yai-law unreadable or invalid)");
    return yai_porcelain_err_exit_code(YAI_PORCELAIN_ERR_DEP_MISSING);
  }

  if (!token1 || !token1[0]) {
    rc = render_global_help(&idx, &sb);
  } else if (strcmp(token1, "--groups") == 0 || strcmp(token1, "-g") == 0) {
    sb_appendf(&sb, "YAI command groups\n");
    render_group_lines(&idx, &sb);
    rc = 0;
  } else if (strcmp(token1, "--all") == 0 || strcmp(token1, "-a") == 0) {
    for (size_t i = 0; i < idx.group_count; i++) {
      const yai_sdk_command_group_t *g = &idx.groups[i];
      for (size_t j = 0; j < g->command_count; j++) {
        sb_appendf(&sb, "%s-%s\n", g->group, g->commands[j].name);
      }
    }
    rc = 0;
  } else if (strncmp(token1, "yai.", 4) == 0) {
    rc = render_command_help(yai_sdk_command_catalog_find_by_id(&idx, token1), &sb);
  } else if (token2 && token2[0]) {
    rc = render_command_help(yai_sdk_command_catalog_find_command(&idx, token1, token2), &sb);
  } else {
    const yai_sdk_command_group_t *g = yai_sdk_command_catalog_find_group(&idx, token1);
    if (g) {
      rc = render_group_help(g, &sb);
    } else {
      const char *dash = strchr(token1, '-');
      if (dash && dash[1]) {
        char group[32];
        size_t glen = (size_t)(dash - token1);
        if (glen < sizeof(group)) {
          memcpy(group, token1, glen);
          group[glen] = '\0';
          rc = render_command_help(yai_sdk_command_catalog_find_command(&idx, group, dash + 1), &sb);
        } else {
          rc = help_error("unknown help topic", "try: yai help --groups");
        }
      } else {
        rc = help_error("unknown help topic", "try: yai help --groups");
      }
    }
  }

  if (rc == 0 && sb.buf) {
    yai_cli_page_if_needed(sb.buf, pager, no_pager);
  }
  sb_free(&sb);
  yai_sdk_command_catalog_free(&idx);
  return rc;
}

int yai_porcelain_help_print_any(const char *token)
{
  return yai_porcelain_help_print(token, NULL, 0, 0);
}
