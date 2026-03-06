/* SPDX-License-Identifier: Apache-2.0 */

#include "watch_internal.h"

#include "yai_cli/color.h"
#include "yai_cli/style_map.h"
#include "yai_cli/screen.h"

#include <stdio.h>
#include <string.h>

static const char *sev_label(yai_watch_severity_t sev)
{
  switch (sev) {
    case YAI_WATCH_OK: return "OK";
    case YAI_WATCH_WARN: return "WARN";
    default: return "ERR";
  }
}

static const char *sev_color(yai_watch_severity_t sev)
{
  switch (sev) {
    case YAI_WATCH_OK: return yai_style_color(YAI_STYLE_OK);
    case YAI_WATCH_WARN: return yai_style_color(YAI_STYLE_WARN);
    default: return yai_style_color(YAI_STYLE_ERR);
  }
}

static yai_watch_severity_t current_sev(const yai_watch_model_t *m)
{
  const yai_watch_entry_t *last;
  if (!m || m->count == 0) return YAI_WATCH_WARN;
  last = yai_watch_model_at(m, m->count - 1U);
  return last ? last->sev : YAI_WATCH_WARN;
}

void yai_watch_ui_render(const yai_watch_model_t *m,
                         int width,
                         int height,
                         const char *cmd,
                         int interval_ms,
                         int use_color,
                         int no_clear)
{
  size_t max_rows;
  size_t vis;
  size_t start;
  yai_watch_severity_t sev = current_sev(m);
  (void)width;
  yai_screen_begin_frame(!no_clear);

  yai_color_print(stdout, use_color, yai_style_color(YAI_STYLE_INFO), "YAI watch");
  printf("  command=%s  interval=%dms  status=", cmd ? cmd : "", interval_ms);
  yai_color_print(stdout, use_color, sev_color(sev), sev_label(sev));
  printf("\n");
  yai_color_print(stdout, use_color, yai_style_color(YAI_STYLE_MUTED),
                  "q quit · space pause · r refresh · ↑↓ scroll · / filter · c clear · j view · ? help");
  printf("\n");

  if (m && m->show_help) {
    puts("");
    puts("Watch help");
    puts("  q/ESC: quit, space: pause, r: refresh, ↑/↓: scroll");
    puts("  g/G: top/bottom, c: clear, j: view toggle, /: filter");
  }

  if (m && m->filter_input_mode) {
    printf("Filter: %s_\n", m->filter);
  } else if (m && m->filter[0]) {
    printf("Filter: %s\n", m->filter);
  }

  if (!m) {
    yai_screen_end_frame();
    return;
  }

  vis = yai_watch_model_visible_count(m);
  max_rows = (height > 7) ? (size_t)(height - 7) : 4U;
  start = 0U;
  if (vis > max_rows) {
    size_t end_pos = vis - m->scroll;
    if (end_pos > max_rows) start = end_pos - max_rows;
  }

  for (size_t i = start; i < vis; i++) {
    const yai_watch_entry_t *e = yai_watch_model_at(m, i);
    if (!e) continue;
    if (m->filter[0] && !strstr(e->summary, m->filter) && !strstr(e->raw, m->filter)) continue;
    printf("%s ", e->ts);
    yai_color_print(stdout, use_color, sev_color(e->sev), sev_label(e->sev));
    printf(" %s\n", (m->view == YAI_WATCH_VIEW_JSON) ? e->raw : e->summary);
    if (m->view == YAI_WATCH_VIEW_HUMAN && e->latency_ms >= 0) {
      yai_color_print(stdout, use_color, yai_style_color(YAI_STYLE_MUTED), "  latency=");
      printf("%ldms\n", e->latency_ms);
    }
  }

  yai_color_print(stdout, use_color, yai_style_color(YAI_STYLE_MUTED), "Counters:");
  printf(" ok=%d warn=%d err=%d  last=%ldms\n",
         m->ok_count, m->warn_count, m->err_count, m->last_latency_ms);
  yai_screen_end_frame();
}
