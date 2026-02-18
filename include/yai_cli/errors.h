#ifndef YAI_CLI_ERRORS_H
#define YAI_CLI_ERRORS_H

typedef enum {
    YAI_CLI_OK = 0,
    YAI_CLI_BAD_ARGS = 2,
    YAI_CLI_IO = 10,
    YAI_CLI_RPC = 20,
    YAI_CLI_PROTOCOL = 30,
    YAI_CLI_NOT_IMPLEMENTED = 99
} yai_cli_err_t;

static inline const char* yai_cli_err_str(int code) {
    switch (code) {
        case YAI_CLI_OK: return "ok";
        case YAI_CLI_BAD_ARGS: return "bad_args";
        case YAI_CLI_IO: return "io";
        case YAI_CLI_RPC: return "rpc";
        case YAI_CLI_PROTOCOL: return "protocol";
        case YAI_CLI_NOT_IMPLEMENTED: return "not_implemented";
        default: return "unknown";
    }
}

#endif
