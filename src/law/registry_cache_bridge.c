// SPDX-License-Identifier: Apache-2.0
// src/law/registry_cache_bridge.c

#include "yai_cli/law/law_registry_cache.h"
#include "yai_cli/law/law_registry_cache_gen.h"   // <-- aggiungi QUESTO
#include <string.h>
const yai_law_registry_t* yai_law_registry_cache(void);
void yai_law_registry_cache_init(yai_law_registry_cache_t *cache)
{
  if (!cache) return;
  memset(cache, 0, sizeof(*cache));
  cache->loaded = 0;
}

void yai_law_registry_cache_clear(yai_law_registry_cache_t *cache)
{
  if (!cache) return;
  memset(&cache->registry, 0, sizeof(cache->registry));
  cache->loaded = 0;
}

int yai_law_registry_cache_load(yai_law_registry_cache_t *cache)
{
  if (!cache) return 1;
  if (cache->loaded) return 0;

  const yai_law_registry_t *r = yai_law_registry_cache(); // provided by generated file
  if (!r) return 2;

  cache->registry = *r;   // shallow copy OK (static tables)
  cache->loaded = 1;
  return 0;
}

const yai_law_registry_t *yai_law_registry_cache_get(const yai_law_registry_cache_t *cache)
{
  if (!cache || !cache->loaded) return NULL;
  return &cache->registry;
}