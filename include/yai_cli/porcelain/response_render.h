// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "yai_sdk/ops/executor.h"

#ifdef __cplusplus
extern "C" {
#endif

int yai_render_exec_short(const yai_exec_result_t *out, int rc);
int yai_render_exec_verbose(const yai_exec_result_t *out, int rc);

#ifdef __cplusplus
}
#endif
