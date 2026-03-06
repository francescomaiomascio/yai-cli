/* SPDX-License-Identifier: Apache-2.0 */
#pragma once

#include <stddef.h>

typedef enum yai_watch_severity {
  YAI_WATCH_OK = 0,
  YAI_WATCH_WARN,
  YAI_WATCH_ERR
} yai_watch_severity_t;

typedef enum yai_watch_view {
  YAI_WATCH_VIEW_HUMAN = 0,
  YAI_WATCH_VIEW_COMPACT = 1,
  YAI_WATCH_VIEW_JSON = 2
} yai_watch_view_t;

typedef struct yai_watch_entry {
  char ts[32];
  int rc;
  long latency_ms;
  yai_watch_severity_t sev;
  char summary[256];
  char raw[1024];
} yai_watch_entry_t;

typedef struct yai_watch_model {
  yai_watch_entry_t entries[50];
  size_t count;
  size_t head;
  size_t scroll;
  int paused;
  int show_help;
  yai_watch_view_t view;
  int ok_count;
  int warn_count;
  int err_count;
  long last_latency_ms;
  char last_trace[128];
  char filter[128];
  int filter_input_mode;
} yai_watch_model_t;

void yai_watch_model_init(yai_watch_model_t *m);
void yai_watch_model_push(yai_watch_model_t *m, const yai_watch_entry_t *e);
void yai_watch_model_clear(yai_watch_model_t *m);
size_t yai_watch_model_visible_count(const yai_watch_model_t *m);
const yai_watch_entry_t *yai_watch_model_at(const yai_watch_model_t *m, size_t index_from_oldest);
void yai_watch_ui_render(const yai_watch_model_t *m,
                         int width,
                         int height,
                         const char *cmd,
                         int interval_ms,
                         int use_color,
                         int no_clear);
