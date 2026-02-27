// src/law/registry_query.c
#include "yai_cli/law/law_registry.h"

#include <stdlib.h>
#include <string.h>

typedef struct idx_entry {
  const char* key; // command id
  const yai_law_command_t* cmd;
} idx_entry_t;

typedef struct group_entry {
  const char* group;
  const yai_law_command_t** items;
  size_t len;
} group_entry_t;

static int g_inited = 0;

static idx_entry_t* g_id_index = NULL;
static size_t g_id_index_len = 0;

static group_entry_t* g_groups = NULL;
static size_t g_groups_len = 0;

static int cmp_id_entry(const void* a, const void* b) {
  const idx_entry_t* x = (const idx_entry_t*)a;
  const idx_entry_t* y = (const idx_entry_t*)b;
  if (!x->key && !y->key) return 0;
  if (!x->key) return -1;
  if (!y->key) return 1;
  return strcmp(x->key, y->key);
}

static int cmp_cstr(const void* a, const void* b) {
  const char* const* x = (const char* const*)a;
  const char* const* y = (const char* const*)b;
  if (!*x && !*y) return 0;
  if (!*x) return -1;
  if (!*y) return 1;
  return strcmp(*x, *y);
}

static const idx_entry_t* bsearch_id(const char* id) {
  if (!g_id_index || g_id_index_len == 0) return NULL;
  idx_entry_t needle = { .key = id, .cmd = NULL };
  return (const idx_entry_t*)bsearch(&needle, g_id_index, g_id_index_len, sizeof(idx_entry_t), cmp_id_entry);
}

static ssize_t find_group_slot(const char* group) {
  for (size_t i = 0; i < g_groups_len; i++) {
    if (g_groups[i].group && strcmp(g_groups[i].group, group) == 0) return (ssize_t)i;
  }
  return -1;
}

int yai_law_registry_init(void) {
  if (g_inited) return 0;

  const yai_law_registry_t* r = yai_law_registry_cache();
  if (!r) return 1;

  // Build id index
  g_id_index_len = r->commands_len;
  if (g_id_index_len > 0) {
    g_id_index = (idx_entry_t*)calloc(g_id_index_len, sizeof(idx_entry_t));
    if (!g_id_index) return 2;
    for (size_t i = 0; i < g_id_index_len; i++) {
      g_id_index[i].key = r->commands[i].id;
      g_id_index[i].cmd = &r->commands[i];
    }
    qsort(g_id_index, g_id_index_len, sizeof(idx_entry_t), cmp_id_entry);
  }

  // Build group lists (two-pass)
  // 1) collect unique group strings
  const char** groups_tmp = NULL;
  size_t groups_tmp_len = 0;

  if (r->commands_len > 0) {
    groups_tmp = (const char**)calloc(r->commands_len, sizeof(char*));
    if (!groups_tmp) return 3;

    for (size_t i = 0; i < r->commands_len; i++) {
      groups_tmp[groups_tmp_len++] = r->commands[i].group;
    }

    qsort(groups_tmp, groups_tmp_len, sizeof(char*), cmp_cstr);

    // count unique
    size_t unique = 0;
    const char* prev = NULL;
    for (size_t i = 0; i < groups_tmp_len; i++) {
      const char* g = groups_tmp[i];
      if (!g) continue;
      if (!prev || strcmp(prev, g) != 0) {
        unique++;
        prev = g;
      }
    }

    g_groups_len = unique;
    g_groups = (group_entry_t*)calloc(g_groups_len, sizeof(group_entry_t));
    if (!g_groups) {
      free(groups_tmp);
      return 4;
    }

    // init groups with names
    size_t gi = 0;
    prev = NULL;
    for (size_t i = 0; i < groups_tmp_len; i++) {
      const char* g = groups_tmp[i];
      if (!g) continue;
      if (!prev || strcmp(prev, g) != 0) {
        g_groups[gi].group = g;
        g_groups[gi].items = NULL;
        g_groups[gi].len = 0;
        gi++;
        prev = g;
      }
    }

    // 2) count per group
    for (size_t i = 0; i < r->commands_len; i++) {
      const char* g = r->commands[i].group;
      if (!g) continue;
      ssize_t slot = find_group_slot(g);
      if (slot >= 0) g_groups[slot].len++;
    }

    // alloc arrays
    for (size_t i = 0; i < g_groups_len; i++) {
      if (g_groups[i].len == 0) continue;
      g_groups[i].items = (const yai_law_command_t**)calloc(g_groups[i].len, sizeof(yai_law_command_t*));
      if (!g_groups[i].items) {
        free(groups_tmp);
        return 5;
      }
      g_groups[i].len = 0; // reuse as cursor
    }

    // fill arrays
    for (size_t i = 0; i < r->commands_len; i++) {
      const yai_law_command_t* c = &r->commands[i];
      if (!c->group) continue;
      ssize_t slot = find_group_slot(c->group);
      if (slot >= 0) {
        group_entry_t* ge = &g_groups[slot];
        ge->items[ge->len++] = c;
      }
    }

    free(groups_tmp);
  }

  g_inited = 1;
  return 0;
}

const yai_law_registry_t* yai_law_registry(void) {
  return yai_law_registry_cache();
}

const yai_law_command_t* yai_law_cmd_by_id(const char* id) {
  if (!g_inited) {
    if (yai_law_registry_init() != 0) return NULL;
  }
  const idx_entry_t* e = bsearch_id(id);
  return e ? e->cmd : NULL;
}

yai_law_cmd_list_t yai_law_cmds_by_group(const char* group) {
  yai_law_cmd_list_t out = { .items = NULL, .len = 0 };

  if (!g_inited) {
    if (yai_law_registry_init() != 0) return out;
  }
  if (!group) return out;

  for (size_t i = 0; i < g_groups_len; i++) {
    if (g_groups[i].group && strcmp(g_groups[i].group, group) == 0) {
      out.items = g_groups[i].items;
      out.len = g_groups[i].len;
      return out;
    }
  }
  return out;
}

int yai_law_command_has_output(const yai_law_command_t* c, const char* out) {
  if (!c || !out) return 0;
  for (size_t i = 0; i < c->outputs_len; i++) {
    if (c->outputs[i] && strcmp(c->outputs[i], out) == 0) return 1;
  }
  return 0;
}

int yai_law_command_has_side_effect(const yai_law_command_t* c, const char* eff) {
  if (!c || !eff) return 0;
  for (size_t i = 0; i < c->side_effects_len; i++) {
    if (c->side_effects[i] && strcmp(c->side_effects[i], eff) == 0) return 1;
  }
  return 0;
}