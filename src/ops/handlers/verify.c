#include <yai_cli/cli.h>
#include <yai_cli/rpc.h>
#include <stdio.h>
#include <string.h>

/*
 * yai test
 *
 * Placeholder harness.
 *
 * Future:
 *  - wire to docs/runbooks/
 *  - execute vectors from resolved specs root (YAI_SPECS_DIR or repo fallback)
 *  - protocol conformance checks
 */

static void usage(void) {
    fprintf(stderr,
        "YAI Test Harness\n"
        "Usage:\n"
        "  yai test\n"
        "  yai test --help\n"
    );
}

static int emit_ok(const char *detail) {
    printf("{\"status\":\"ok\",\"code\":\"TEST_PLACEHOLDER\",\"detail\":\"%s\"}\n",
           detail ? detail : "no tests wired");
    return 0;
}

int yai_cmd_test(int argc, char **argv, const yai_cli_opts_t *opt) {
    (void)opt;

    if (argc > 0) {
        if (strcmp(argv[0], "--help") == 0 ||
            strcmp(argv[0], "-h") == 0) {
            usage();
            return 0;
        }

        // future: subcommands (protocol, law, engine, etc)
        fprintf(stderr,
                "{\"status\":\"error\",\"code\":\"UNKNOWN_SUBCOMMAND\"}\n");
        return 2;
    }

    // No side effects. Deterministic output.
    return emit_ok("no tests wired");
}
