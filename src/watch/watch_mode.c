/* SPDX-License-Identifier: Apache-2.0 */

#include "yai_cli/watch/watch_mode.h"
#include "yai_cli/util/terminal.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

static volatile sig_atomic_t g_running = 1;

static void on_sigint(int signo)
{
  (void)signo;
  g_running = 0;
}

static size_t append_shell_escaped(char *dst, size_t cap, size_t off, const char *s)
{
  if (!s) s = "";
  if (off + 1 < cap) dst[off++] = '\'';
  for (size_t i = 0; s[i] && off + 5 < cap; i++) {
    if (s[i] == '\'') {
      dst[off++] = '\'';
      dst[off++] = '\\';
      dst[off++] = '\'';
      dst[off++] = '\'';
    } else {
      dst[off++] = s[i];
    }
  }
  if (off + 1 < cap) dst[off++] = '\'';
  if (off < cap) dst[off] = '\0';
  return off;
}

static int run_once_and_print(int argc, char **argv)
{
  char cmd[4096];
  char tmp[256];
  size_t off = 0;
  FILE *f;
  int rc;
  snprintf(tmp, sizeof(tmp), "/tmp/yai-watch-%ld.out", (long)getpid());
  off += (size_t)snprintf(cmd + off, sizeof(cmd) - off, "./dist/bin/yai");
  for (int i = 0; i < argc && off + 8 < sizeof(cmd); i++) {
    off += (size_t)snprintf(cmd + off, sizeof(cmd) - off, " ");
    off = append_shell_escaped(cmd, sizeof(cmd), off, argv[i]);
  }
  off += (size_t)snprintf(cmd + off, sizeof(cmd) - off, " > %s 2>&1", tmp);
  rc = system(cmd);
  (void)rc;
  f = fopen(tmp, "r");
  if (!f) {
    puts("watch: cannot read command output");
    return 1;
  }
  while (!feof(f)) {
    char line[512];
    if (!fgets(line, sizeof(line), f)) break;
    fputs(line, stdout);
  }
  fclose(f);
  unlink(tmp);
  return 0;
}

int yai_watch_mode_run(int argc, char **argv, int interval_sec)
{
  if (argc <= 0 || !argv || !argv[0]) {
    fputs("watch: missing command\n", stderr);
    return 20;
  }
  if (interval_sec <= 0) interval_sec = 1;
  signal(SIGINT, on_sigint);
  while (g_running) {
    yai_term_clear();
    puts("YAI Watch Mode");
    printf("Command: ");
    for (int i = 0; i < argc; i++) {
      if (i) putchar(' ');
      fputs(argv[i], stdout);
    }
    putchar('\n');
    printf("Interval: %ds\n", interval_sec);
    puts("Press Ctrl+C to exit");
    puts("");
    (void)run_once_and_print(argc, argv);
    fflush(stdout);
    sleep((unsigned int)interval_sec);
  }
  return 0;
}
