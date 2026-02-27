#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Lifecycle
int yai_ops_lifecycle_up(int argc, char** argv);
int yai_ops_lifecycle_restart(int argc, char** argv);
int yai_ops_lifecycle_down(int argc, char** argv);

// Inspect
int yai_ops_inspect_status(int argc, char** argv);
int yai_ops_inspect_logs(int argc, char** argv);
int yai_ops_inspect_monitor(int argc, char** argv);
int yai_ops_inspect_events(int argc, char** argv);

// Verify
int yai_ops_verify_verify(int argc, char** argv);
int yai_ops_verify_test(int argc, char** argv);

// Control
int yai_ops_control_root(int argc, char** argv);
int yai_ops_control_kernel(int argc, char** argv);
int yai_ops_control_sessions(int argc, char** argv);
int yai_ops_control_providers(int argc, char** argv);
int yai_ops_control_chat(int argc, char** argv);
int yai_ops_control_shell(int argc, char** argv);
int yai_ops_control_dsar(int argc, char** argv);
int yai_ops_control_workspace(int argc, char** argv);

#ifdef __cplusplus
}
#endif