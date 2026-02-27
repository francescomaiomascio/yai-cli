// src/law/registry_load.c
#include "yai_cli/law/law_registry.h"
#include "yai_cli/law/law_registry_cache.h"
#include "yai_cli/law/law_registry_validate.h"

#include <stddef.h>

static const yai_law_registry_t* g_reg = NULL;
static int g_inited = 0;
static int g_init_rc = 1;

int yai_law_registry_init(void) {
  if (g_inited) return g_init_rc;
  g_inited = 1;

  // 1) Get embedded registry (generated).
  const yai_law_registry_t* reg = yai_law_registry_cache_get();
  if (!reg) {
    g_reg = NULL;
    g_init_rc = 1;
    return g_init_rc;
  }

  // 2) Validate (fast structural checks; no IO).
  if (yai_law_registry_validate(reg) != 0) {
    g_reg = NULL;
    g_init_rc = 1;
    return g_init_rc;
  }

  // 3) Publish.
  g_reg = reg;
  g_init_rc = 0;
  return g_init_rc;
}

const yai_law_registry_t* yai_law_registry(void) {
  return g_reg;
}