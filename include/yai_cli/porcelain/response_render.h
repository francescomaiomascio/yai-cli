// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <yai_sdk/client.h>

#ifdef __cplusplus
extern "C" {
#endif

int yai_render_exec_short(const yai_sdk_reply_t *out, int rc);
int yai_render_exec_verbose(const yai_sdk_reply_t *out, int rc, const char *control_call_json);
int yai_render_exec_json(const yai_sdk_reply_t *out);
int yai_render_exec_exit_code(const yai_sdk_reply_t *out, int sdk_rc);

#ifdef __cplusplus
}
#endif
