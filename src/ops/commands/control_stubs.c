/* SPDX-License-Identifier: Apache-2.0 */
// src/ops/commands/control_stubs.c

#include <yai_cli/ops/ops.h>
#include <stdio.h>

static int not_impl(const char *name) {
  fprintf(stderr, "ERR: not implemented (%s)\n", name);
  return 2;
}

int yai_ops_control_sessions(int argc, char **argv) { (void)argc; (void)argv; return not_impl("sessions"); }
int yai_ops_control_chat(int argc, char **argv)     { (void)argc; (void)argv; return not_impl("chat"); }
int yai_ops_control_shell(int argc, char **argv)    { (void)argc; (void)argv; return not_impl("shell"); }
int yai_ops_control_dsar(int argc, char **argv)     { (void)argc; (void)argv; return not_impl("dsar"); }