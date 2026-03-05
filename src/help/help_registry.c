/* SPDX-License-Identifier: Apache-2.0 */

#include "yai_cli/help/help_registry.h"

#include "yai_sdk/registry/registry_registry.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int cmp_group(const void *a, const void *b)
{
  const yai_help_group_t *ga = (const yai_help_group_t *)a;
  const yai_help_group_t *gb = (const yai_help_group_t *)b;
  return strcmp(ga->group, gb->group);
}

static int cmp_cmd(const void *a, const void *b)
{
  const yai_help_command_t *ca = (const yai_help_command_t *)a;
  const yai_help_command_t *cb = (const yai_help_command_t *)b;
  return strcmp(ca->command, cb->command);
}

static const yai_help_group_t *find_group_internal(const yai_help_index_t *idx, const char *group, size_t *pos)
{
  if (pos) *pos = 0;
  if (!idx || !group || !group[0]) return NULL;
  for (size_t i = 0; i < idx->group_count; i++) {
    if (strcmp(idx->groups[i].group, group) == 0) {
      if (pos) *pos = i;
      return &idx->groups[i];
    }
  }
  return NULL;
}

int yai_help_registry_load(yai_help_index_t *out)
{
  const yai_law_registry_t *reg;
  if (!out) return 1;
  memset(out, 0, sizeof(*out));

  if (yai_law_registry_init() != 0) return 2;
  reg = yai_law_registry();
  if (!reg || !reg->commands || reg->commands_len == 0) return 3;

  out->groups = (yai_help_group_t *)calloc(reg->commands_len, sizeof(yai_help_group_t));
  if (!out->groups) return 4;

  for (size_t i = 0; i < reg->commands_len; i++) {
    const yai_law_command_t *c = &reg->commands[i];
    size_t gi = 0;
    yai_help_group_t *g;
    yai_help_command_t *slot;
    if (!c || !c->group || !c->name || !c->id) continue;
    if (!find_group_internal(out, c->group, &gi)) {
      gi = out->group_count++;
      snprintf(out->groups[gi].group, sizeof(out->groups[gi].group), "%s", c->group);
      out->groups[gi].commands = (yai_help_command_t *)calloc(reg->commands_len, sizeof(yai_help_command_t));
      if (!out->groups[gi].commands) return 5;
    }
    g = &out->groups[gi];
    slot = &g->commands[g->command_count++];
    snprintf(slot->group, sizeof(slot->group), "%s", c->group);
    snprintf(slot->command, sizeof(slot->command), "%s", c->name);
    snprintf(slot->canonical_id, sizeof(slot->canonical_id), "%s", c->id);
    if (c->summary && c->summary[0]) {
      snprintf(slot->description, sizeof(slot->description), "%s", c->summary);
    } else {
      snprintf(slot->description, sizeof(slot->description), "No description.");
    }
  }

  qsort(out->groups, out->group_count, sizeof(out->groups[0]), cmp_group);
  for (size_t i = 0; i < out->group_count; i++) {
    qsort(out->groups[i].commands, out->groups[i].command_count, sizeof(out->groups[i].commands[0]), cmp_cmd);
  }
  return 0;
}

void yai_help_registry_free(yai_help_index_t *idx)
{
  if (!idx) return;
  if (idx->groups) {
    for (size_t i = 0; i < idx->group_count; i++) {
      free(idx->groups[i].commands);
      idx->groups[i].commands = NULL;
      idx->groups[i].command_count = 0;
    }
    free(idx->groups);
  }
  memset(idx, 0, sizeof(*idx));
}

const yai_help_group_t *yai_help_registry_find_group(const yai_help_index_t *idx, const char *group)
{
  return find_group_internal(idx, group, NULL);
}

const yai_help_command_t *yai_help_registry_find_command(const yai_help_index_t *idx, const char *group, const char *command)
{
  const yai_help_group_t *g = yai_help_registry_find_group(idx, group);
  if (!g || !command) return NULL;
  for (size_t i = 0; i < g->command_count; i++) {
    if (strcmp(g->commands[i].command, command) == 0) return &g->commands[i];
  }
  return NULL;
}

const yai_help_command_t *yai_help_registry_find_by_id(const yai_help_index_t *idx, const char *canonical_id)
{
  if (!idx || !canonical_id || !canonical_id[0]) return NULL;
  for (size_t i = 0; i < idx->group_count; i++) {
    const yai_help_group_t *g = &idx->groups[i];
    for (size_t j = 0; j < g->command_count; j++) {
      if (strcmp(g->commands[j].canonical_id, canonical_id) == 0) return &g->commands[j];
    }
  }
  return NULL;
}
