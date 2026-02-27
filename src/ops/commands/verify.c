/* SPDX-License-Identifier: Apache-2.0 */
// src/ops/commands/verify.c

#define _POSIX_C_SOURCE 200809L

#include <yai_cli/ops/ops.h>

#include <stdio.h>
#include <string.h>

static void usage_test(void) {
    fprintf(stderr,
        "YAI Test Harness\n"
        "Usage:\n"
        "  yai test\n"
        "  yai test --help\n");
}

static int emit_ok(const char *detail) {
    printf("{\"status\":\"ok\",\"code\":\"TEST_PLACEHOLDER\",\"detail\":\"%s\"}\n",
           detail ? detail : "no tests wired");
    return 0;
}

/* yai.verify.test */
int yai_ops_verify_test(int argc, char **argv)
{
    if (argc > 0) {
        if (strcmp(argv[0], "--help") == 0 || strcmp(argv[0], "-h") == 0) {
            usage_test();
            return 0;
        }
        fprintf(stderr, "{\"status\":\"error\",\"code\":\"UNKNOWN_SUBCOMMAND\"}\n");
        return 2;
    }

    return emit_ok("no tests wired");
}

/* yai.verify.verify — stub for now */
int yai_ops_verify_verify(int argc, char **argv)
{
    (void)argc; (void)argv;
    fprintf(stderr, "{\"status\":\"error\",\"code\":\"NOT_IMPLEMENTED\"}\n");
    return 2;
}