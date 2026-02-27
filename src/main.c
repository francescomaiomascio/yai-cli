/* SPDX-License-Identifier: Apache-2.0 */
// src/main.c

#include <yai_cli/porcelain/porcelain.h>

#include <stdio.h>

#ifndef YAI_CLI_VERSION
#define YAI_CLI_VERSION "yai-cli/1.0"
#endif

int main(int argc, char **argv)
{
    (void)argv;

    /* Keep main minimal: porcelain owns parsing, registry lookup, help, errors. */
    if (argc == 2) {
        /* Extremely lightweight convenience, so `yai --version` works even
           before registry is loaded (useful during bring-up / broken deps). */
        if (argv[1] && (strcmp(argv[1], "-V") == 0 || strcmp(argv[1], "--version") == 0)) {
            printf("%s\n", YAI_CLI_VERSION);
            return 0;
        }
    }

    return yai_porcelain_run(argc, argv);
}