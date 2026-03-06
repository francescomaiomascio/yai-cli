// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "yai_sdk/client.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Legacy local alias: renderer now consumes SDK client reply surface. */
typedef yai_sdk_reply_t yai_exec_result_t;

int yai_render_exec_short(const yai_exec_result_t *out, int rc);
int yai_render_exec_verbose(const yai_exec_result_t *out, int rc);

#ifdef __cplusplus
}
#endif
