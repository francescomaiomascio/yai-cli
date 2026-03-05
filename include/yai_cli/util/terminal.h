/* SPDX-License-Identifier: Apache-2.0 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

int yai_term_width(void);
int yai_term_height(void);
int yai_term_is_tty(void);
void yai_term_clear(void);

#ifdef __cplusplus
}
#endif
