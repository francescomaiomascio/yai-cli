// SPDX-License-Identifier: Apache-2.0
// src/law/registry_cache_bridge.c

#include "yai_cli/law/law_registry_cache.h"
#include "yai_cli/law/law_paths.h"
#include "yai_cli/porcelain/porcelain_errors.h"

#include <errno.h>
#include <string.h>

/*
 * Runtime-load bridge:
 * - resolve deps/yai-law paths
 * - load registry JSON files into cache->registry (deep copy)
 */

void yai_law_registry_cache_init(yai_law_registry_cache_t *cache)
{
  if (!cache) return;
  memset(cache, 0, sizeof(*cache));
  cache->loaded = 0;
}

void yai_law_registry_cache_clear(yai_law_registry_cache_t *cache)
{
  if (!cache) return;
  yai_law_registry_cache_free(cache);   // <-- nuova funzione (vedi punto 2)
  memset(cache, 0, sizeof(*cache));
  cache->loaded = 0;
}

int yai_law_registry_cache_load(yai_law_registry_cache_t *cache)
{
  if (!cache) return EINVAL;
  if (cache->loaded) return 0;

  yai_law_paths_t paths;
  int rc = yai_law_paths_init(&paths, NULL);
  if (rc != 0) return rc;

  rc = yai_law_registry_cache_load_from_files(
      cache,
      yai_law_registry_commands(&paths),
      yai_law_registry_artifacts(&paths)
      /* primitives optional per ora */
  );

  yai_law_paths_free(&paths);
  return rc;
}

const yai_law_registry_t *yai_law_registry_cache_get(const yai_law_registry_cache_t *cache)
{
  if (!cache || !cache->loaded) return NULL;
  return &cache->registry;
}