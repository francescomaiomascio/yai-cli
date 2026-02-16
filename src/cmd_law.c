#include "../include/yai_cmd_law.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define LAW_PATH_MAX 512

static int file_exists(const char *p) {
    struct stat st;
    return (p && p[0] && stat(p, &st) == 0 && S_ISREG(st.st_mode));
}

static int dir_exists(const char *p) {
    struct stat st;
    return (p && p[0] && stat(p, &st) == 0 && S_ISDIR(st.st_mode));
}

typedef struct {
    const char *rel_path;
    int must_be_dir;
} law_req_t;

static const law_req_t REQ[] = {
    { "control/control_plane.v1.json", 0 },
    { "control/authority.json",        0 },
    { "protocol/protocol.h",           0 },
    { "protocol/transport.h",          0 },
    { "protocol/yai_protocol_ids.h",   0 },
    { NULL, 0 }
};

/*
 * Resolve specs root dynamically.
 * Priority:
 *   1) YAI_SPECS_DIR (explicit override)
 *   2) repository-relative fallbacks
 */
static int find_specs_root(char *out, size_t cap) {
    if (!out || cap < 8) return 0;

    const char *env = getenv("YAI_SPECS_DIR");
    if (env && env[0]) {
        if (dir_exists(env)) {
            int n = snprintf(out, cap, "%s", env);
            return (n > 0 && (size_t)n < cap);
        }
    }

    static const char *PREFIXES[] = {
        "",
        "../",
        "../../",
        "../../../",
        NULL
    };
    static const char *ROOTS[] = {
        "deps/yai-specs",
        "contracts",
        NULL
    };

    for (int i = 0; PREFIXES[i]; i++) {
        for (int j = 0; ROOTS[j]; j++) {
            char path[LAW_PATH_MAX];
            int n = snprintf(path, sizeof(path), "%s%s", PREFIXES[i], ROOTS[j]);
            if (n > 0 && (size_t)n < sizeof(path) && dir_exists(path)) {
                n = snprintf(out, cap, "%s", path);
                return (n > 0 && (size_t)n < cap);
            }
        }
    }

    return 0;
}

static void law_usage(void) {
    fprintf(stderr,
        "YAI Law (local)\n"
        "Usage:\n"
        "  yai law check    # verify core specs exist\n"
        "  yai law tree     # print logical structure\n"
        "  yai law status   # exit 0 if specs root is found, else 2\n"
    );
}

static int cmd_check(void) {
    char specs_root[LAW_PATH_MAX];
    if (!find_specs_root(specs_root, sizeof(specs_root))) {
        fprintf(stderr, "[law][FATAL] specs root not found. Set YAI_SPECS_DIR or run from repo root.\n");
        return 2;
    }

    int ok = 1;
    printf("[law] Integrity check (specs root: %s)\n", specs_root);

    for (int i = 0; REQ[i].rel_path; i++) {
        char full[LAW_PATH_MAX];
        int n = snprintf(full, sizeof(full), "%s/%s",
                         specs_root, REQ[i].rel_path);

        if (n <= 0 || (size_t)n >= sizeof(full)) {
            fprintf(stderr, "  [FAIL] %s (path overflow)\n",
                    REQ[i].rel_path);
            ok = 0;
            continue;
        }

        int exists = REQ[i].must_be_dir
            ? dir_exists(full)
            : file_exists(full);

        if (exists) {
            printf("  [OK]   %s\n", REQ[i].rel_path);
        } else {
            fprintf(stderr, "  [FAIL] %s (missing)\n",
                    REQ[i].rel_path);
            ok = 0;
        }
    }

    if (ok) {
        printf("\n[law] Status: PROVISIONS_MET\n");
        return 0;
    }

    fprintf(stderr, "\n[law] Status: VIOLATION_DETECTED\n");
    return 2;
}

static int cmd_tree(void) {
    puts("specs/ (resolved by YAI_SPECS_DIR or repo fallbacks)");
    puts("└── [deps/yai-specs | contracts]/");
    puts("    ├── control/");
    puts("    ├── protocol/");
    puts("    └── ...");
    return 0;
}

static int cmd_status(void) {
    char specs_root[LAW_PATH_MAX];
    if (find_specs_root(specs_root, sizeof(specs_root))) {
        printf("[law] FOUND (specs root: %s)\n", specs_root);
        return 0;
    }

    fprintf(stderr, "[law] NOT_FOUND\n");
    return 2;
}

int yai_cmd_law(int argc, char **argv, const yai_cli_opts_t *opt) {
    (void)opt;

    if (argc < 1) {
        law_usage();
        return 1;
    }

    const char *sub = argv[0];

    if (strcmp(sub, "check") == 0)  return cmd_check();
    if (strcmp(sub, "tree") == 0)   return cmd_tree();
    if (strcmp(sub, "status") == 0) return cmd_status();

    fprintf(stderr, "ERR: unknown law subcommand: %s\n", sub);
    law_usage();
    return 1;
}
