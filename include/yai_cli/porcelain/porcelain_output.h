// include/yai_cli/porcelain/porcelain_output.h
#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Minimal “table” helpers (stable text output; json later).
void yai_porcelain_out_kv(const char* k, const char* v);
void yai_porcelain_out_heading(const char* title);
void yai_porcelain_out_list_item(const char* s);
void yai_porcelain_out_table2(const char* h1, const char* h2,
                              const char* const* c1, const char* const* c2, size_t n);

#ifdef __cplusplus
}
#endif