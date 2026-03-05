/* SPDX-License-Identifier: Apache-2.0 */

#include "yai_cli/util/pager.h"
#include "yai_cli/util/terminal.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int count_lines(const char *s)
{
  int lines = 0;
  if (!s || !s[0]) return 0;
  for (size_t i = 0; s[i]; i++) {
    if (s[i] == '\n') lines++;
  }
  return lines + 1;
}

static int env_pager_enabled(void)
{
  const char *v = getenv("YAI_PAGER");
  if (!v) return 0;
  return (strcmp(v, "1") == 0 || strcmp(v, "true") == 0) ? 1 : 0;
}

void yai_cli_page_if_needed(const char *text, int force_pager, int no_pager)
{
  int lines;
  int height;
  int enabled;
  FILE *f;
  char tmp[256];
  char cmd[320];
  if (!text) return;
  if (no_pager) {
    fputs(text, stdout);
    return;
  }
  enabled = force_pager || env_pager_enabled();
  if (!enabled || !yai_term_is_tty()) {
    fputs(text, stdout);
    return;
  }
  lines = count_lines(text);
  height = yai_term_height();
  if (lines <= height) {
    fputs(text, stdout);
    return;
  }
  snprintf(tmp, sizeof(tmp), "/tmp/yai-pager-%ld.txt", (long)getpid());
  f = fopen(tmp, "w");
  if (!f) {
    fputs(text, stdout);
    return;
  }
  fputs(text, f);
  fclose(f);
  snprintf(cmd, sizeof(cmd), "less -R %s", tmp);
  (void)system(cmd);
  unlink(tmp);
}
