// include/yai_cli/porcelain/porcelain_help.h
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// token meanings:
// - NULL => global help
// - "<group>" => list commands in group
// - "yai.<group>.<name>" => show command details
int yai_porcelain_help_print_any(const char* token);

#ifdef __cplusplus
}
#endif