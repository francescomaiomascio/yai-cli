// include/yai_cli/porcelain/porcelain.h
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Porcelain entrypoint. Returns process exit code.
int yai_porcelain_run(int argc, char** argv);

#ifdef __cplusplus
}
#endif