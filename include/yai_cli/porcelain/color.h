/* SPDX-License-Identifier: Apache-2.0 */
#pragma once

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define YAI_COLOR_RESET "\x1b[0m"
#define YAI_COLOR_GREEN "\x1b[32m"
#define YAI_COLOR_YELLOW "\x1b[33m"
#define YAI_COLOR_RED "\x1b[31m"
#define YAI_COLOR_CYAN "\x1b[36m"

int yai_color_enabled(FILE *stream, int no_color_flag);

#ifdef __cplusplus
}
#endif

