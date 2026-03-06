/* SPDX-License-Identifier: Apache-2.0 */

#define _POSIX_C_SOURCE 200809L

#include "yai_cli/watch.h"

#include "watch_internal.h"

#include "yai_cli/color.h"
#include "yai_cli/keys.h"
#include "yai_cli/term.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

static volatile sig_atomic_t g_running = 1;

static void on_signal_stop(int signo)
{
  (void)signo;
  g_running = 0;
}

static int is_watch_opt(const char *s)
{
  return s && (
      strcmp(s, "--interval-ms") == 0 ||
      strcmp(s, "--interval") == 0 ||
      strcmp(s, "--count") == 0 ||
      strcmp(s, "--no-clear") == 0 ||
      strcmp(s, "--once") == 0);
}

static int watch_opt_has_value(const char *s)
{
  return (s &&
          (strcmp(s, "--interval-ms") == 0 ||
           strcmp(s, "--interval") == 0 ||
           strcmp(s, "--count") == 0));
}

static int build_exec_argv(int argc, char **argv, char **out, int cap)
{
  int n = 0;
  for (int i = 0; i < argc && n < cap; i++) {
    if (!argv || !argv[i]) continue;
    if (is_watch_opt(argv[i])) {
      if (watch_opt_has_value(argv[i]) && i + 1 < argc) i++;
      continue;
    }
    out[n++] = argv[i];
  }
  return n;
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

static void now_ts(char *out, size_t cap)
{
  time_t now = time(NULL);
  struct tm tmv;
  if (!out || cap == 0) return;
  out[0] = '\0';
  if (localtime_r(&now, &tmv)) {
    strftime(out, cap, "%H:%M:%S", &tmv);
  }
}

static long monotonic_ms(void)
{
  struct timespec ts;
  if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) return 0;
  return (long)(ts.tv_sec * 1000L + ts.tv_nsec / 1000000L);
}

static yai_watch_severity_t severity_from_rc(int rc)
{
  if (rc == 0) return YAI_WATCH_OK;
  if (rc == 10 || rc == 40) return YAI_WATCH_WARN;
  return YAI_WATCH_ERR;
}

static int run_once_capture(int argc, char **argv, yai_watch_entry_t *entry)
{
  char cmd[4096];
  char tmp[256];
  FILE *f;
  size_t off = 0;
  int status;
  long t0;
  long t1;
  if (!entry) return 1;
  memset(entry, 0, sizeof(*entry));
  now_ts(entry->ts, sizeof(entry->ts));
  snprintf(tmp, sizeof(tmp), "/tmp/yai-watch-%ld.out", (long)getpid());

  off += (size_t)snprintf(cmd + off, sizeof(cmd) - off, "./dist/bin/yai");
  for (int i = 0; i < argc && off + 8 < sizeof(cmd); i++) {
    off += (size_t)snprintf(cmd + off, sizeof(cmd) - off, " ");
    off = append_shell_escaped(cmd, sizeof(cmd), off, argv[i]);
  }
  (void)snprintf(cmd + off, sizeof(cmd) - off, " > %s 2>&1", tmp);

  t0 = monotonic_ms();
  status = system(cmd);
  t1 = monotonic_ms();
  entry->latency_ms = (t1 >= t0) ? (t1 - t0) : -1;
  if (status == -1) entry->rc = 50;
  else if (WIFEXITED(status)) entry->rc = WEXITSTATUS(status);
  else entry->rc = 50;
  entry->sev = severity_from_rc(entry->rc);

  f = fopen(tmp, "r");
  if (!f) {
    snprintf(entry->summary, sizeof(entry->summary), "watch: cannot read output");
    snprintf(entry->raw, sizeof(entry->raw), "{\"error\":\"watch_read_failed\"}");
    return 1;
  }
  {
    char line[512];
    size_t rawlen = 0;
    int got_summary = 0;
    while (fgets(line, sizeof(line), f)) {
      size_t ll = strlen(line);
      if (rawlen + ll + 1 < sizeof(entry->raw)) {
        memcpy(entry->raw + rawlen, line, ll);
        rawlen += ll;
      }
      if (!got_summary && ll > 0) {
        while (ll > 0 && (line[ll - 1] == '\n' || line[ll - 1] == '\r')) line[--ll] = '\0';
        snprintf(entry->summary, sizeof(entry->summary), "%s", line[0] ? line : "(empty)");
        got_summary = 1;
      }
    }
    entry->raw[rawlen] = '\0';
    if (!got_summary) snprintf(entry->summary, sizeof(entry->summary), "(no output)");
  }
  fclose(f);
  unlink(tmp);
  return 0;
}

static void build_cmd_label(int argc, char **argv, char *out, size_t cap)
{
  size_t off = 0;
  if (!out || cap == 0) return;
  out[0] = '\0';
  for (int i = 0; i < argc; i++) {
    if (!argv || !argv[i]) continue;
    off += (size_t)snprintf(out + off, (off < cap) ? cap - off : 0, "%s%s", (i ? " " : ""), argv[i]);
    if (off + 1 >= cap) break;
  }
}

static void handle_key(yai_watch_model_t *m, const yai_key_event_t *ev)
{
  size_t vis;
  if (!m || !ev) return;
  vis = yai_watch_model_visible_count(m);
  if (m->filter_input_mode) {
    size_t len = strlen(m->filter);
    if (ev->code == YAI_KEY_ENTER) {
      m->filter_input_mode = 0;
      return;
    }
    if (ev->code == YAI_KEY_CHAR && (unsigned char)ev->ch == 127) {
      if (len > 0) m->filter[len - 1] = '\0';
      return;
    }
    if (ev->code == YAI_KEY_CHAR && ev->ch >= 32 && ev->ch < 127 && len + 1 < sizeof(m->filter)) {
      m->filter[len] = ev->ch;
      m->filter[len + 1] = '\0';
    }
    return;
  }

  if (ev->code == YAI_KEY_ESC || (ev->code == YAI_KEY_CHAR && (ev->ch == 'q' || ev->ch == 3))) {
    g_running = 0;
    return;
  }
  if (ev->code == YAI_KEY_CHAR && ev->ch == ' ') { m->paused = !m->paused; return; }
  if (ev->code == YAI_KEY_CHAR && ev->ch == 'c') { yai_watch_model_clear(m); return; }
  if (ev->code == YAI_KEY_CHAR && ev->ch == '?') { m->show_help = !m->show_help; return; }
  if (ev->code == YAI_KEY_CHAR && ev->ch == 'j') { m->view = (yai_watch_view_t)(((int)m->view + 1) % 3); return; }
  if (ev->code == YAI_KEY_CHAR && ev->ch == '/') { m->filter_input_mode = 1; m->filter[0] = '\0'; return; }
  if (ev->code == YAI_KEY_UP || (ev->code == YAI_KEY_CHAR && ev->ch == 'k')) { if (m->scroll + 1 < vis) m->scroll++; return; }
  if (ev->code == YAI_KEY_DOWN || (ev->code == YAI_KEY_CHAR && ev->ch == 'n')) { if (m->scroll > 0) m->scroll--; return; }
  if (ev->code == YAI_KEY_CHAR && ev->ch == 'g') { m->scroll = (vis > 0) ? (vis - 1) : 0; return; }
  if (ev->code == YAI_KEY_CHAR && ev->ch == 'G') { m->scroll = 0; return; }
}

static void non_tty_watch(int argc, char **argv, int interval_ms, int count)
{
  int iter = 0;
  if (count <= 0) count = 5;
  while (g_running && iter < count) {
    yai_watch_entry_t e;
    run_once_capture(argc, argv, &e);
    printf("%s rc=%d %s\n", e.ts, e.rc, e.summary);
    fflush(stdout);
    iter++;
    if (iter >= count) break;
    {
      struct timespec ts;
      ts.tv_sec = interval_ms / 1000;
      ts.tv_nsec = (long)(interval_ms % 1000) * 1000000L;
      while (nanosleep(&ts, &ts) != 0 && g_running) {
      }
    }
  }
}

int yai_watch_mode_run(int argc, char **argv, int interval_ms, int count, int no_clear, int no_color)
{
  char *exec_argv[256];
  int exec_argc;
  int iter = 0;
  int is_tty;
  int use_color;
  long next_tick;
  yai_term_raw_state_t raw = {0};
  yai_watch_model_t model;
  char cmd_label[512];

  if (argc <= 0 || !argv || !argv[0]) {
    fputs("watch: missing command\n", stderr);
    return 20;
  }
  if (interval_ms <= 0) interval_ms = 1000;
  exec_argc = build_exec_argv(argc, argv, exec_argv, (int)(sizeof(exec_argv) / sizeof(exec_argv[0])));
  if (exec_argc <= 0) {
    fputs("watch: missing command\n", stderr);
    return 20;
  }

  build_cmd_label(exec_argc, exec_argv, cmd_label, sizeof(cmd_label));
  signal(SIGINT, on_signal_stop);
  signal(SIGTERM, on_signal_stop);
  is_tty = yai_term_is_tty();
  if (!is_tty) {
    non_tty_watch(exec_argc, exec_argv, interval_ms, count);
    return 0;
  }

  use_color = yai_color_enabled(stdout, no_color, YAI_COLOR_AUTO);
  yai_watch_model_init(&model);
  yai_term_alt_screen_enter();
  yai_term_cursor_hide();
  (void)yai_term_enable_raw_mode(&raw);

  next_tick = monotonic_ms();
  while (g_running) {
    long now = monotonic_ms();
    if (!model.paused && now >= next_tick) {
      yai_watch_entry_t e;
      run_once_capture(exec_argc, exec_argv, &e);
      yai_watch_model_push(&model, &e);
      iter++;
      next_tick = now + interval_ms;
      if (count > 0 && iter >= count) break;
    }

    yai_watch_ui_render(&model, yai_term_width(), yai_term_height(), cmd_label, interval_ms, use_color, no_clear);
    {
      yai_key_event_t ev;
      if (yai_keys_read(&ev, 100)) {
        if (ev.code == YAI_KEY_CHAR && ev.ch == 'r') next_tick = monotonic_ms();
        else handle_key(&model, &ev);
      }
    }
  }

  yai_term_disable_raw_mode(&raw);
  yai_term_cursor_show();
  yai_term_alt_screen_leave();
  yai_term_clear();
  return 0;
}
