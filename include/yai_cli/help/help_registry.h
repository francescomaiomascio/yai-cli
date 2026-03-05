/* SPDX-License-Identifier: Apache-2.0 */
#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  char group[32];
  char command[64];
  char description[160];
  char canonical_id[128];
} yai_help_command_t;

typedef struct {
  char group[32];
  size_t command_count;
  yai_help_command_t *commands;
} yai_help_group_t;

typedef struct {
  size_t group_count;
  yai_help_group_t *groups;
} yai_help_index_t;

int yai_help_registry_load(yai_help_index_t *out);
void yai_help_registry_free(yai_help_index_t *idx);
const yai_help_group_t *yai_help_registry_find_group(const yai_help_index_t *idx, const char *group);
const yai_help_command_t *yai_help_registry_find_command(const yai_help_index_t *idx, const char *group, const char *command);
const yai_help_command_t *yai_help_registry_find_by_id(const yai_help_index_t *idx, const char *canonical_id);

#ifdef __cplusplus
}
#endif
