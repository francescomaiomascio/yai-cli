// include/yai_cli/porcelain/porcelain_parse.h
#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum yai_porcelain_kind_e {
  YAI_PORCELAIN_KIND_NONE = 0,
  YAI_PORCELAIN_KIND_HELP,
  YAI_PORCELAIN_KIND_LAW,     // "yai law ..."
  YAI_PORCELAIN_KIND_COMMAND, // "yai <group> <name> ..."
  YAI_PORCELAIN_KIND_ERROR
} yai_porcelain_kind_t;

typedef struct yai_porcelain_request_s {
  yai_porcelain_kind_t kind;

  // For HELP:
  const char* help_token;

  // For COMMAND:
  const char* command_id;
  int cmd_argc;
  char** cmd_argv;

  // For LAW:
  int law_argc;
  char** law_argv;

  // For ERROR:
  const char* error;
} yai_porcelain_request_t;

int yai_porcelain_parse_argv(int argc, char** argv, yai_porcelain_request_t* req);

#ifdef __cplusplus
}
#endif