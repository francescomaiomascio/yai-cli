/* SPDX-License-Identifier: Apache-2.0 */

#include <yai_cli/cmd.h>   // keeps ABI stable for now (yai_cmd_dispatch signature)
#include <yai_cli/fmt.h>

#include <yai_cli/porcelain/porcelain.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Central Sovereign Dispatcher (v1: registry-driven)
 *
 * Old world: hand-coded routing (root/kernel/engine/mind/law).
 * New world: porcelain + law registry decide what a command is,
 *            then ops_dispatch routes by canonical command id.
 *
 * This function remains as a compatibility shim because src/main.c calls it.
 */

static void usage_global(void)
{
    fprintf(stderr,
        "YAI Sovereign CLI\n"
        "\n"
        "Usage:\n"
        "  yai <command> [args]\n"
        "\n"
        "Try:\n"
        "  yai help\n"
        "  yai help --all\n"
        "  yai help <group>\n"
        "  yai help <command>\n"
        "\n"
        "This CLI is registry-driven. Canonical command set is loaded from:\n"
        "  deps/yai-law/law/abi/registry/commands.v1.json\n"
    );
}

int yai_cmd_dispatch(
    const char *binary,
    int argc,
    char **argv,
    const yai_cli_opts_t *opt
)
{
    (void)opt; // porcelain re-parses args for now (can be threaded later)

    // In existing main.c calls, `binary` is the *target command token* (e.g. "status"),
    // and `argv` is the remaining tail. We rebuild a "normal main()" argv vector.
    if (!binary || !binary[0]) {
        usage_global();
        return 2;
    }

    // Build: ["yai", binary, argv...]
    int full_argc = argc + 2;
    char **full_argv = (char**)calloc((size_t)full_argc + 1, sizeof(char*));
    if (!full_argv) {
        fprintf(stderr, "FATAL: out of memory\n");
        return 1;
    }

    full_argv[0] = (char*)"yai";
    full_argv[1] = (char*)binary;
    for (int i = 0; i < argc; i++) {
        full_argv[i + 2] = argv[i];
    }
    full_argv[full_argc] = NULL;

    // registry-driven execution
    int rc = yai_porcelain_run(full_argc, full_argv);

    // If porcelain returns a "usage-like" code, print a minimal global usage too.
    if (rc == 2) {
        // avoid double-noise: porcelain likely printed command-specific help
        // but global usage is still useful when entrypoint token is unknown.
        // Keep it short.
        // (If you prefer: remove this block.)
        // usage_global();
    }

    free(full_argv);
    return rc;
}