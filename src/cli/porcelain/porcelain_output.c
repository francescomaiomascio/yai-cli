// src/porcelain/porcelain_output.c
#include "yai_cli/porcelain/porcelain_output.h"

#include <stdio.h>

void yai_porcelain_out_kv(const char* k, const char* v) {
  if (!k) k = "";
  if (!v) v = "";
  printf("%s: %s\n", k, v);
}

void yai_porcelain_out_heading(const char* title) {
  if (!title) title = "";
  printf("\n%s\n", title);
  for (const char* p = title; *p; p++) putchar('=');
  putchar('\n');
}

void yai_porcelain_out_list_item(const char* s) {
  if (!s) s = "";
  printf("- %s\n", s);
}

void yai_porcelain_out_table2(const char* h1, const char* h2,
                              const char* const* c1, const char* const* c2, size_t n) {
  if (!h1) h1 = "";
  if (!h2) h2 = "";
  printf("%-24s  %s\n", h1, h2);
  printf("%-24s  %s\n", "------------------------", "------------------------");
  for (size_t i = 0; i < n; i++) {
    const char* a = c1 ? c1[i] : "";
    const char* b = c2 ? c2[i] : "";
    printf("%-24s  %s\n", a ? a : "", b ? b : "");
  }
}