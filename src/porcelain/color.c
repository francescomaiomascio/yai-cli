/* SPDX-License-Identifier: Apache-2.0 */

#include "yai_cli/porcelain/color.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int yai_color_enabled(FILE *stream, int no_color_flag)
{
  int fd = STDOUT_FILENO;
  if (!stream) return 0;
  if (no_color_flag) return 0;
  if (getenv("NO_COLOR") != NULL) return 0;
  if (stream == stderr) fd = STDERR_FILENO;
  return isatty(fd) ? 1 : 0;
}
