/* SPDX-License-Identifier: Apache-2.0 */

#include "yai_cli/util/terminal.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

int yai_term_width(void)
{
  struct winsize ws;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0 && ws.ws_col > 0) return (int)ws.ws_col;
  return 80;
}

int yai_term_height(void)
{
  struct winsize ws;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0 && ws.ws_row > 0) return (int)ws.ws_row;
  return 24;
}

int yai_term_is_tty(void)
{
  return isatty(STDOUT_FILENO) ? 1 : 0;
}

void yai_term_clear(void)
{
  fputs("\033[H\033[J", stdout);
}
