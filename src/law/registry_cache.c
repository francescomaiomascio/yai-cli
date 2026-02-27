// AUTO-GENERATED. DO NOT EDIT.
#include "yai_cli/law/law_registry_cache.h"
#include <stddef.h>
#include <string.h>

// ---- artifacts registry ----
static const yai_law_artifact_role_t g_artifacts[6] = {
  {
    .role = "bundle_manifest",
    .schema_ref = "schema/bundle_manifest.v1.schema.json",
    .description = "Bundle manifest (root of truth): bundle_id, timestamps, and hashed artifact inventory.",
  },
  {
    .role = "verification_report",
    .schema_ref = "schema/verification_report.v1.schema.json",
    .description = "Offline verification output (PASS/FAIL) with findings and exit_code.",
  },
  {
    .role = "decision_record",
    .schema_ref = "schema/decision_record.v1.schema.json",
    .description = "Decision record line (JSONL): event -> policy+authority evaluation -> outcome+reason_code (+ optional effect).",
  },
  {
    .role = "policy",
    .schema_ref = "schema/policy.v1.schema.json",
    .description = "Policy material bound to baseline+contract_ref, hashed for reproducibility.",
  },
  {
    .role = "containment_metrics",
    .schema_ref = "schema/containment_metrics.v1.schema.json",
    .description = "Aggregated containment metrics for a run/wave (typed values with units).",
  },
  {
    .role = "evidence_index",
    .schema_ref = "schema/evidence_index.v1.schema.json",
    .description = "Evidence inventory: role->path->sha256 (+ optional size/content_type) for verification.",
  },
};

// ---- commands registry ----
static const yai_law_arg_t cmd_yai_lifecycle_up_args[8] = {
  {
    .name = "ws",
    .flag = "--ws",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "build",
    .flag = "--build",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "ai",
    .flag = "--ai",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "no_engine",
    .flag = "--no-engine",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "no_mind",
    .flag = "--no-mind",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "detach",
    .flag = "--detach",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "monitor",
    .flag = "--monitor",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "timeout_ms",
    .flag = "--timeout-ms",
    .pos = 0,
    .type = "int",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_lifecycle_up_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_lifecycle_up_side_effects[5] = {
  "spawn_processes",
  "write_session",
  "write_logs",
  "create_socket",
  "rpc_call",
};
static const char* cmd_yai_lifecycle_up_law_hooks[6] = {
  "I-001",
  "I-002",
  "I-006",
  "L1",
  "L2",
  "L3",
};
static const char* cmd_yai_lifecycle_up_law_invariants[3] = {
  "I-001-traceability",
  "I-002-determinism",
  "I-006-external-effect-boundary",
};
static const char* cmd_yai_lifecycle_up_law_boundaries[3] = {
  "L1-kernel",
  "L2-engine",
  "L3-mind",
};
static const char* cmd_yai_lifecycle_up_uses_primitives[7] = {
  "O-004",
  "O-005",
  "S-016",
  "S-023",
  "S-026",
  "S-029",
  "T-012",
};
static const yai_law_command_t cmd_yai_lifecycle_up = {
  .id = "yai.lifecycle.up",
  .name = "up",
  .group = "lifecycle",
  .summary = "Start stack: boot + engine + mind",
  .args = cmd_yai_lifecycle_up_args,
  .args_len = 8,
  .outputs = cmd_yai_lifecycle_up_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_lifecycle_up_side_effects,
  .side_effects_len = 5,
  .law_hooks = cmd_yai_lifecycle_up_law_hooks,
  .law_hooks_len = 6,
  .law_invariants = cmd_yai_lifecycle_up_law_invariants,
  .law_invariants_len = 3,
  .law_boundaries = cmd_yai_lifecycle_up_law_boundaries,
  .law_boundaries_len = 3,
  .uses_primitives = cmd_yai_lifecycle_up_uses_primitives,
  .uses_primitives_len = 7,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const yai_law_arg_t cmd_yai_lifecycle_restart_args[9] = {
  {
    .name = "ws",
    .flag = "--ws",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "build",
    .flag = "--build",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "ai",
    .flag = "--ai",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "no_engine",
    .flag = "--no-engine",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "no_mind",
    .flag = "--no-mind",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "detach",
    .flag = "--detach",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "monitor",
    .flag = "--monitor",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "timeout_ms",
    .flag = "--timeout-ms",
    .pos = 0,
    .type = "int",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "force",
    .flag = "--force",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_lifecycle_restart_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_lifecycle_restart_side_effects[6] = {
  "signal_processes",
  "spawn_processes",
  "write_session",
  "write_logs",
  "create_socket",
  "rpc_call",
};
static const char* cmd_yai_lifecycle_restart_law_hooks[6] = {
  "I-001",
  "I-002",
  "I-006",
  "L1",
  "L2",
  "L3",
};
static const char* cmd_yai_lifecycle_restart_law_invariants[3] = {
  "I-001-traceability",
  "I-002-determinism",
  "I-006-external-effect-boundary",
};
static const char* cmd_yai_lifecycle_restart_law_boundaries[3] = {
  "L1-kernel",
  "L2-engine",
  "L3-mind",
};
static const char* cmd_yai_lifecycle_restart_uses_primitives[7] = {
  "O-004",
  "O-005",
  "S-016",
  "S-023",
  "S-026",
  "S-029",
  "T-012",
};
static const yai_law_command_t cmd_yai_lifecycle_restart = {
  .id = "yai.lifecycle.restart",
  .name = "restart",
  .group = "lifecycle",
  .summary = "Restart stack for a workspace",
  .args = cmd_yai_lifecycle_restart_args,
  .args_len = 9,
  .outputs = cmd_yai_lifecycle_restart_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_lifecycle_restart_side_effects,
  .side_effects_len = 6,
  .law_hooks = cmd_yai_lifecycle_restart_law_hooks,
  .law_hooks_len = 6,
  .law_invariants = cmd_yai_lifecycle_restart_law_invariants,
  .law_invariants_len = 3,
  .law_boundaries = cmd_yai_lifecycle_restart_law_boundaries,
  .law_boundaries_len = 3,
  .uses_primitives = cmd_yai_lifecycle_restart_uses_primitives,
  .uses_primitives_len = 7,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const yai_law_arg_t cmd_yai_lifecycle_down_args[2] = {
  {
    .name = "ws",
    .flag = "--ws",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "force",
    .flag = "--force",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_lifecycle_down_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_lifecycle_down_side_effects[4] = {
  "signal_processes",
  "remove_session",
  "remove_socket",
  "rpc_call",
};
static const char* cmd_yai_lifecycle_down_law_hooks[5] = {
  "I-001",
  "I-006",
  "L1",
  "L2",
  "L3",
};
static const char* cmd_yai_lifecycle_down_law_invariants[2] = {
  "I-001-traceability",
  "I-006-external-effect-boundary",
};
static const char* cmd_yai_lifecycle_down_law_boundaries[3] = {
  "L1-kernel",
  "L2-engine",
  "L3-mind",
};
static const char* cmd_yai_lifecycle_down_uses_primitives[5] = {
  "O-004",
  "S-016",
  "S-023",
  "S-026",
  "T-012",
};
static const yai_law_command_t cmd_yai_lifecycle_down = {
  .id = "yai.lifecycle.down",
  .name = "down",
  .group = "lifecycle",
  .summary = "Stop stack and cleanup runtime artifacts",
  .args = cmd_yai_lifecycle_down_args,
  .args_len = 2,
  .outputs = cmd_yai_lifecycle_down_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_lifecycle_down_side_effects,
  .side_effects_len = 4,
  .law_hooks = cmd_yai_lifecycle_down_law_hooks,
  .law_hooks_len = 5,
  .law_invariants = cmd_yai_lifecycle_down_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_lifecycle_down_law_boundaries,
  .law_boundaries_len = 3,
  .uses_primitives = cmd_yai_lifecycle_down_uses_primitives,
  .uses_primitives_len = 5,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const yai_law_arg_t cmd_yai_inspect_status_args[2] = {
  {
    .name = "ws",
    .flag = "--ws",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "json",
    .flag = "--json",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_inspect_status_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_inspect_status_law_hooks[4] = {
  "I-001",
  "L1",
  "L2",
  "L3",
};
static const char* cmd_yai_inspect_status_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_inspect_status_law_boundaries[3] = {
  "L1-kernel",
  "L2-engine",
  "L3-mind",
};
static const char* cmd_yai_inspect_status_uses_primitives[3] = {
  "S-026",
  "S-016",
  "S-002",
};
static const yai_law_command_t cmd_yai_inspect_status = {
  .id = "yai.inspect.status",
  .name = "status",
  .group = "inspect",
  .summary = "Show runtime status (pids, socket, vault readiness)",
  .args = cmd_yai_inspect_status_args,
  .args_len = 2,
  .outputs = cmd_yai_inspect_status_outputs,
  .outputs_len = 2,
  .side_effects = NULL,
  .side_effects_len = 0,
  .law_hooks = cmd_yai_inspect_status_law_hooks,
  .law_hooks_len = 4,
  .law_invariants = cmd_yai_inspect_status_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_inspect_status_law_boundaries,
  .law_boundaries_len = 3,
  .uses_primitives = cmd_yai_inspect_status_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_inspect_logs_arg0_values[4] = {
  "boot",
  "engine",
  "mind",
  "kernel",
};
static const yai_law_arg_t cmd_yai_inspect_logs_args[3] = {
  {
    .name = "component",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_inspect_logs_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "ws",
    .flag = "--ws",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "follow",
    .flag = "--follow",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_inspect_logs_outputs[1] = {
  "text",
};
static const char* cmd_yai_inspect_logs_law_hooks[1] = {
  "I-001",
};
static const char* cmd_yai_inspect_logs_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_inspect_logs_uses_primitives[2] = {
  "S-016",
  "S-022",
};
static const yai_law_command_t cmd_yai_inspect_logs = {
  .id = "yai.inspect.logs",
  .name = "logs",
  .group = "inspect",
  .summary = "Tail logs for a component",
  .args = cmd_yai_inspect_logs_args,
  .args_len = 3,
  .outputs = cmd_yai_inspect_logs_outputs,
  .outputs_len = 1,
  .side_effects = NULL,
  .side_effects_len = 0,
  .law_hooks = cmd_yai_inspect_logs_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_inspect_logs_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = NULL,
  .law_boundaries_len = 0,
  .uses_primitives = cmd_yai_inspect_logs_uses_primitives,
  .uses_primitives_len = 2,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const yai_law_arg_t cmd_yai_inspect_monitor_args[1] = {
  {
    .name = "ws",
    .flag = "--ws",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_inspect_monitor_outputs[1] = {
  "text",
};
static const char* cmd_yai_inspect_monitor_side_effects[1] = {
  "rpc_call",
};
static const char* cmd_yai_inspect_monitor_law_hooks[4] = {
  "I-001",
  "L1",
  "L2",
  "L3",
};
static const char* cmd_yai_inspect_monitor_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_inspect_monitor_law_boundaries[3] = {
  "L1-kernel",
  "L2-engine",
  "L3-mind",
};
static const char* cmd_yai_inspect_monitor_uses_primitives[4] = {
  "S-016",
  "S-022",
  "S-010",
  "T-001",
};
static const yai_law_command_t cmd_yai_inspect_monitor = {
  .id = "yai.inspect.monitor",
  .name = "monitor",
  .group = "inspect",
  .summary = "Live monitor (event stream) for a workspace",
  .args = cmd_yai_inspect_monitor_args,
  .args_len = 1,
  .outputs = cmd_yai_inspect_monitor_outputs,
  .outputs_len = 1,
  .side_effects = cmd_yai_inspect_monitor_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_inspect_monitor_law_hooks,
  .law_hooks_len = 4,
  .law_invariants = cmd_yai_inspect_monitor_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_inspect_monitor_law_boundaries,
  .law_boundaries_len = 3,
  .uses_primitives = cmd_yai_inspect_monitor_uses_primitives,
  .uses_primitives_len = 4,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const yai_law_arg_t cmd_yai_inspect_events_args[1] = {
  {
    .name = "ws",
    .flag = "--ws",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_inspect_events_outputs[1] = {
  "text",
};
static const char* cmd_yai_inspect_events_side_effects[1] = {
  "rpc_call",
};
static const char* cmd_yai_inspect_events_law_hooks[4] = {
  "I-001",
  "L1",
  "L2",
  "L3",
};
static const char* cmd_yai_inspect_events_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_inspect_events_law_boundaries[3] = {
  "L1-kernel",
  "L2-engine",
  "L3-mind",
};
static const char* cmd_yai_inspect_events_uses_primitives[4] = {
  "S-016",
  "S-022",
  "S-010",
  "T-001",
};
static const yai_law_command_t cmd_yai_inspect_events = {
  .id = "yai.inspect.events",
  .name = "events",
  .group = "inspect",
  .summary = "Stream daemon events (NDJSON)",
  .args = cmd_yai_inspect_events_args,
  .args_len = 1,
  .outputs = cmd_yai_inspect_events_outputs,
  .outputs_len = 1,
  .side_effects = cmd_yai_inspect_events_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_inspect_events_law_hooks,
  .law_hooks_len = 4,
  .law_invariants = cmd_yai_inspect_events_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_inspect_events_law_boundaries,
  .law_boundaries_len = 3,
  .uses_primitives = cmd_yai_inspect_events_uses_primitives,
  .uses_primitives_len = 4,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_verify_verify_arg0_values[2] = {
  "core",
  "full",
};
static const yai_law_arg_t cmd_yai_verify_verify_args[1] = {
  {
    .name = "target",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_verify_verify_arg0_values,
    .values_len = 2,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_verify_verify_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_verify_verify_side_effects[2] = {
  "spawn_processes",
  "run_scripts",
};
static const char* cmd_yai_verify_verify_law_hooks[3] = {
  "I-003",
  "I-001",
  "Lx",
};
static const char* cmd_yai_verify_verify_law_invariants[2] = {
  "I-003-governance",
  "I-001-traceability",
};
static const char* cmd_yai_verify_verify_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_verify_verify_uses_primitives[5] = {
  "T-015",
  "T-014",
  "S-008",
  "S-014",
  "O-007",
};
static const yai_law_artifact_io_t cmd_yai_verify_verify_emits_artifacts[1] = {
  {
    .role = "verification_report",
    .schema_ref = "schema/verification_report.v1.schema.json",
    .path_hint = "verify/report.json",
  },
};
static const yai_law_artifact_io_t cmd_yai_verify_verify_consumes_artifacts[1] = {
  {
    .role = "bundle_manifest",
    .schema_ref = "schema/bundle_manifest.v1.schema.json",
    .path_hint = "bundle/**",
  },
};
static const yai_law_command_t cmd_yai_verify_verify = {
  .id = "yai.verify.verify",
  .name = "verify",
  .group = "verify",
  .summary = "Run verification gates",
  .args = cmd_yai_verify_verify_args,
  .args_len = 1,
  .outputs = cmd_yai_verify_verify_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_verify_verify_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_verify_verify_law_hooks,
  .law_hooks_len = 3,
  .law_invariants = cmd_yai_verify_verify_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_verify_verify_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_verify_verify_uses_primitives,
  .uses_primitives_len = 5,
  .emits_artifacts = cmd_yai_verify_verify_emits_artifacts,
  .emits_artifacts_len = 1,
  .consumes_artifacts = cmd_yai_verify_verify_consumes_artifacts,
  .consumes_artifacts_len = 1,
};

static const char* cmd_yai_verify_test_arg0_values[1] = {
  "smoke",
};
static const yai_law_arg_t cmd_yai_verify_test_args[3] = {
  {
    .name = "target",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_verify_test_arg0_values,
    .values_len = 1,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "ws",
    .flag = "--ws",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "timeout_ms",
    .flag = "--timeout-ms",
    .pos = 0,
    .type = "int",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_verify_test_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_verify_test_side_effects[1] = {
  "spawn_processes",
};
static const char* cmd_yai_verify_test_law_hooks[4] = {
  "I-001",
  "L1",
  "L2",
  "L3",
};
static const char* cmd_yai_verify_test_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_verify_test_law_boundaries[3] = {
  "L1-kernel",
  "L2-engine",
  "L3-mind",
};
static const char* cmd_yai_verify_test_uses_primitives[4] = {
  "O-009",
  "S-026",
  "S-016",
  "T-012",
};
static const yai_law_command_t cmd_yai_verify_test = {
  .id = "yai.verify.test",
  .name = "test",
  .group = "verify",
  .summary = "Run test gates",
  .args = cmd_yai_verify_test_args,
  .args_len = 3,
  .outputs = cmd_yai_verify_test_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_verify_test_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_verify_test_law_hooks,
  .law_hooks_len = 4,
  .law_invariants = cmd_yai_verify_test_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_verify_test_law_boundaries,
  .law_boundaries_len = 3,
  .uses_primitives = cmd_yai_verify_test_uses_primitives,
  .uses_primitives_len = 4,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_control_providers_arg0_values[8] = {
  "discover",
  "list",
  "trust",
  "pair",
  "attach",
  "detach",
  "revoke",
  "status",
};
static const yai_law_arg_t cmd_yai_control_providers_args[2] = {
  {
    .name = "subcommand",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_control_providers_arg0_values,
    .values_len = 8,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "ws",
    .flag = "--ws",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_control_providers_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_control_providers_side_effects[3] = {
  "rpc_call",
  "write_trust",
  "write_session",
};
static const char* cmd_yai_control_providers_law_hooks[2] = {
  "I-001",
  "L3",
};
static const char* cmd_yai_control_providers_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_control_providers_law_boundaries[1] = {
  "L3-mind",
};
static const char* cmd_yai_control_providers_uses_primitives[5] = {
  "S-006",
  "S-005",
  "S-016",
  "T-002",
  "T-003",
};
static const yai_law_command_t cmd_yai_control_providers = {
  .id = "yai.control.providers",
  .name = "providers",
  .group = "control",
  .summary = "Provider lifecycle (discover/pair/attach/detach/status)",
  .args = cmd_yai_control_providers_args,
  .args_len = 2,
  .outputs = cmd_yai_control_providers_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_control_providers_side_effects,
  .side_effects_len = 3,
  .law_hooks = cmd_yai_control_providers_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_control_providers_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_control_providers_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_control_providers_uses_primitives,
  .uses_primitives_len = 5,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_control_dsar_arg0_values[3] = {
  "request",
  "status",
  "execute",
};
static const yai_law_arg_t cmd_yai_control_dsar_args[2] = {
  {
    .name = "subcommand",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_control_dsar_arg0_values,
    .values_len = 3,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "ws",
    .flag = "--ws",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_control_dsar_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_control_dsar_side_effects[1] = {
  "rpc_call",
};
static const char* cmd_yai_control_dsar_law_hooks[2] = {
  "I-001",
  "L3",
};
static const char* cmd_yai_control_dsar_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_control_dsar_law_boundaries[1] = {
  "L3-mind",
};
static const char* cmd_yai_control_dsar_uses_primitives[3] = {
  "S-016",
  "T-003",
  "T-021",
};
static const yai_law_command_t cmd_yai_control_dsar = {
  .id = "yai.control.dsar",
  .name = "dsar",
  .group = "control",
  .summary = "DSAR workflow (request/status/execute)",
  .args = cmd_yai_control_dsar_args,
  .args_len = 2,
  .outputs = cmd_yai_control_dsar_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_control_dsar_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_control_dsar_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_control_dsar_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_control_dsar_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_control_dsar_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_control_sessions_arg0_values[2] = {
  "list",
  "kill",
};
static const yai_law_arg_t cmd_yai_control_sessions_args[3] = {
  {
    .name = "subcommand",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_control_sessions_arg0_values,
    .values_len = 2,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "kill_ws",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "force",
    .flag = "--force",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_control_sessions_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_control_sessions_side_effects[2] = {
  "rpc_call",
  "signal_processes",
};
static const char* cmd_yai_control_sessions_law_hooks[4] = {
  "I-001",
  "L1",
  "L2",
  "L3",
};
static const char* cmd_yai_control_sessions_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_control_sessions_law_boundaries[3] = {
  "L1-kernel",
  "L2-engine",
  "L3-mind",
};
static const char* cmd_yai_control_sessions_uses_primitives[4] = {
  "S-026",
  "S-016",
  "S-023",
  "T-012",
};
static const yai_law_command_t cmd_yai_control_sessions = {
  .id = "yai.control.sessions",
  .name = "sessions",
  .group = "control",
  .summary = "List or kill sessions",
  .args = cmd_yai_control_sessions_args,
  .args_len = 3,
  .outputs = cmd_yai_control_sessions_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_control_sessions_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_control_sessions_law_hooks,
  .law_hooks_len = 4,
  .law_invariants = cmd_yai_control_sessions_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_control_sessions_law_boundaries,
  .law_boundaries_len = 3,
  .uses_primitives = cmd_yai_control_sessions_uses_primitives,
  .uses_primitives_len = 4,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_control_chat_arg0_values[5] = {
  "list",
  "new",
  "select",
  "history",
  "send",
};
static const yai_law_arg_t cmd_yai_control_chat_args[2] = {
  {
    .name = "subcommand",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_control_chat_arg0_values,
    .values_len = 5,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "ws",
    .flag = "--ws",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_control_chat_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_control_chat_side_effects[1] = {
  "rpc_call",
};
static const char* cmd_yai_control_chat_law_hooks[2] = {
  "I-001",
  "L3",
};
static const char* cmd_yai_control_chat_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_control_chat_law_boundaries[1] = {
  "L3-mind",
};
static const char* cmd_yai_control_chat_uses_primitives[3] = {
  "S-016",
  "T-002",
  "S-010",
};
static const yai_law_command_t cmd_yai_control_chat = {
  .id = "yai.control.chat",
  .name = "chat",
  .group = "control",
  .summary = "Chat sessions and messages via control plane",
  .args = cmd_yai_control_chat_args,
  .args_len = 2,
  .outputs = cmd_yai_control_chat_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_control_chat_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_control_chat_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_control_chat_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_control_chat_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_control_chat_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_control_shell_arg0_values[1] = {
  "exec",
};
static const yai_law_arg_t cmd_yai_control_shell_args[2] = {
  {
    .name = "subcommand",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_control_shell_arg0_values,
    .values_len = 1,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "ws",
    .flag = "--ws",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_control_shell_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_control_shell_side_effects[2] = {
  "rpc_call",
  "spawn_processes",
};
static const char* cmd_yai_control_shell_law_hooks[3] = {
  "I-001",
  "I-006",
  "L3",
};
static const char* cmd_yai_control_shell_law_invariants[2] = {
  "I-001-traceability",
  "I-006-external-effect-boundary",
};
static const char* cmd_yai_control_shell_law_boundaries[1] = {
  "L3-mind",
};
static const char* cmd_yai_control_shell_uses_primitives[4] = {
  "S-030",
  "S-029",
  "T-003",
  "T-010",
};
static const yai_law_command_t cmd_yai_control_shell = {
  .id = "yai.control.shell",
  .name = "shell",
  .group = "control",
  .summary = "Capability-gated shell execution via control plane",
  .args = cmd_yai_control_shell_args,
  .args_len = 2,
  .outputs = cmd_yai_control_shell_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_control_shell_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_control_shell_law_hooks,
  .law_hooks_len = 3,
  .law_invariants = cmd_yai_control_shell_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_control_shell_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_control_shell_uses_primitives,
  .uses_primitives_len = 4,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_control_root_arg0_values[1] = {
  "ping",
};
static const char* cmd_yai_control_root_arg3_values[2] = {
  "operator",
  "system",
};
static const yai_law_arg_t cmd_yai_control_root_args[4] = {
  {
    .name = "subcommand",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_control_root_arg0_values,
    .values_len = 1,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "ws",
    .flag = "--ws",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "arming",
    .flag = "--arming",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "role",
    .flag = "--role",
    .pos = 0,
    .type = "enum",
    .values = cmd_yai_control_root_arg3_values,
    .values_len = 2,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_control_root_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_control_root_side_effects[1] = {
  "rpc_call",
};
static const char* cmd_yai_control_root_law_hooks[4] = {
  "I-001",
  "I-002",
  "I-003",
  "L1",
};
static const char* cmd_yai_control_root_law_invariants[3] = {
  "I-001-traceability",
  "I-002-determinism",
  "I-003-governance",
};
static const char* cmd_yai_control_root_law_boundaries[1] = {
  "L1-kernel",
};
static const char* cmd_yai_control_root_uses_primitives[4] = {
  "T-003",
  "T-007",
  "S-016",
  "S-002",
};
static const yai_law_command_t cmd_yai_control_root = {
  .id = "yai.control.root",
  .name = "root",
  .group = "control",
  .summary = "Root control-plane probes and handshake-level checks",
  .args = cmd_yai_control_root_args,
  .args_len = 4,
  .outputs = cmd_yai_control_root_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_control_root_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_control_root_law_hooks,
  .law_hooks_len = 4,
  .law_invariants = cmd_yai_control_root_law_invariants,
  .law_invariants_len = 3,
  .law_boundaries = cmd_yai_control_root_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_control_root_uses_primitives,
  .uses_primitives_len = 4,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_control_kernel_arg0_values[2] = {
  "ping",
  "ws",
};
static const char* cmd_yai_control_kernel_arg1_values[3] = {
  "create",
  "destroy",
  "reset",
};
static const char* cmd_yai_control_kernel_arg4_values[2] = {
  "operator",
  "system",
};
static const yai_law_arg_t cmd_yai_control_kernel_args[5] = {
  {
    .name = "subcommand",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_control_kernel_arg0_values,
    .values_len = 2,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "ws_action",
    .flag = NULL,
    .pos = 2,
    .type = "enum",
    .values = cmd_yai_control_kernel_arg1_values,
    .values_len = 3,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "ws",
    .flag = "--ws",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "arming",
    .flag = "--arming",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "role",
    .flag = "--role",
    .pos = 0,
    .type = "enum",
    .values = cmd_yai_control_kernel_arg4_values,
    .values_len = 2,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_control_kernel_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_control_kernel_side_effects[3] = {
  "rpc_call",
  "write_session",
  "remove_session",
};
static const char* cmd_yai_control_kernel_law_hooks[6] = {
  "I-001",
  "I-002",
  "I-003",
  "I-006",
  "L1",
  "L2",
};
static const char* cmd_yai_control_kernel_law_invariants[4] = {
  "I-001-traceability",
  "I-002-determinism",
  "I-003-governance",
  "I-006-external-effect-boundary",
};
static const char* cmd_yai_control_kernel_law_boundaries[2] = {
  "L1-kernel",
  "L2-engine",
};
static const char* cmd_yai_control_kernel_uses_primitives[6] = {
  "T-003",
  "T-007",
  "S-005",
  "S-006",
  "S-023",
  "T-012",
};
static const yai_law_command_t cmd_yai_control_kernel = {
  .id = "yai.control.kernel",
  .name = "kernel",
  .group = "control",
  .summary = "Kernel authority operations and workspace lifecycle",
  .args = cmd_yai_control_kernel_args,
  .args_len = 5,
  .outputs = cmd_yai_control_kernel_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_control_kernel_side_effects,
  .side_effects_len = 3,
  .law_hooks = cmd_yai_control_kernel_law_hooks,
  .law_hooks_len = 6,
  .law_invariants = cmd_yai_control_kernel_law_invariants,
  .law_invariants_len = 4,
  .law_boundaries = cmd_yai_control_kernel_law_boundaries,
  .law_boundaries_len = 2,
  .uses_primitives = cmd_yai_control_kernel_uses_primitives,
  .uses_primitives_len = 6,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_memory_graph_arg0_values[10] = {
  "add-node",
  "add-edge",
  "query",
  "stats",
  "node",
  "neighbors",
  "export",
  "awareness",
  "activate",
  "trace",
};
static const yai_law_arg_t cmd_yai_memory_graph_args[2] = {
  {
    .name = "subcommand",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_memory_graph_arg0_values,
    .values_len = 10,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "ws",
    .flag = "--ws",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_memory_graph_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_memory_graph_side_effects[4] = {
  "write_semantic",
  "read_semantic",
  "write_vector",
  "read_vector",
};
static const char* cmd_yai_memory_graph_law_hooks[2] = {
  "I-001",
  "L3",
};
static const char* cmd_yai_memory_graph_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_memory_graph_law_boundaries[1] = {
  "L3-mind",
};
static const char* cmd_yai_memory_graph_uses_primitives[4] = {
  "S-006",
  "S-005",
  "S-012",
  "T-002",
};
static const yai_law_command_t cmd_yai_memory_graph = {
  .id = "yai.memory.graph",
  .name = "graph",
  .group = "memory",
  .summary = "MindGraph operations (semantic add-node/add-edge, query uses semantic+vector+activation)",
  .args = cmd_yai_memory_graph_args,
  .args_len = 2,
  .outputs = cmd_yai_memory_graph_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_memory_graph_side_effects,
  .side_effects_len = 4,
  .law_hooks = cmd_yai_memory_graph_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_memory_graph_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_memory_graph_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_memory_graph_uses_primitives,
  .uses_primitives_len = 4,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const yai_law_arg_t cmd_yai_memory_embed_args[2] = {
  {
    .name = "model",
    .flag = "--model",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "text",
    .flag = "--text",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_memory_embed_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_memory_embed_side_effects[1] = {
  "read_models",
};
static const char* cmd_yai_memory_embed_law_hooks[2] = {
  "I-001",
  "L3",
};
static const char* cmd_yai_memory_embed_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_memory_embed_law_boundaries[1] = {
  "L3-mind",
};
static const char* cmd_yai_memory_embed_uses_primitives[3] = {
  "S-033",
  "S-016",
  "S-012",
};
static const yai_law_command_t cmd_yai_memory_embed = {
  .id = "yai.memory.embed",
  .name = "embed",
  .group = "memory",
  .summary = "Generate embedding vector",
  .args = cmd_yai_memory_embed_args,
  .args_len = 2,
  .outputs = cmd_yai_memory_embed_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_memory_embed_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_memory_embed_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_memory_embed_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_memory_embed_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_memory_embed_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_ns_arg0_values[4] = {
  "declare",
  "list",
  "resolve",
  "validate",
};
static const yai_law_arg_t cmd_yai_substrate_ns_args[3] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_ns_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "name",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "json",
    .flag = "--json",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_ns_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_ns_law_hooks[2] = {
  "I-001",
  "I-002",
};
static const char* cmd_yai_substrate_ns_law_invariants[2] = {
  "I-001-traceability",
  "I-002-determinism",
};
static const char* cmd_yai_substrate_ns_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_ns_uses_primitives[2] = {
  "S-001",
  "S-010",
};
static const yai_law_command_t cmd_yai_substrate_ns = {
  .id = "yai.substrate.ns",
  .name = "ns",
  .group = "substrate",
  .summary = "Namespace operations (declare/list/resolve/validate)",
  .args = cmd_yai_substrate_ns_args,
  .args_len = 3,
  .outputs = cmd_yai_substrate_ns_outputs,
  .outputs_len = 2,
  .side_effects = NULL,
  .side_effects_len = 0,
  .law_hooks = cmd_yai_substrate_ns_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_substrate_ns_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_substrate_ns_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_ns_uses_primitives,
  .uses_primitives_len = 2,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_ref_arg0_values[4] = {
  "parse",
  "format",
  "resolve",
  "dereference",
};
static const yai_law_arg_t cmd_yai_substrate_ref_args[4] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_ref_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "ref",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "store",
    .flag = "--store",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "json",
    .flag = "--json",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_ref_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_ref_law_hooks[2] = {
  "I-001",
  "I-002",
};
static const char* cmd_yai_substrate_ref_law_invariants[2] = {
  "I-001-traceability",
  "I-002-determinism",
};
static const char* cmd_yai_substrate_ref_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_ref_uses_primitives[3] = {
  "S-002",
  "S-001",
  "S-006",
};
static const yai_law_command_t cmd_yai_substrate_ref = {
  .id = "yai.substrate.ref",
  .name = "ref",
  .group = "substrate",
  .summary = "Ref operations (parse/format/resolve/dereference)",
  .args = cmd_yai_substrate_ref_args,
  .args_len = 4,
  .outputs = cmd_yai_substrate_ref_outputs,
  .outputs_len = 2,
  .side_effects = NULL,
  .side_effects_len = 0,
  .law_hooks = cmd_yai_substrate_ref_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_substrate_ref_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_substrate_ref_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_ref_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_key_arg0_values[5] = {
  "gen",
  "load",
  "fingerprint",
  "sign",
  "verify",
};
static const yai_law_arg_t cmd_yai_substrate_key_args[4] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_key_arg0_values,
    .values_len = 5,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "in",
    .flag = "--in",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "out",
    .flag = "--out",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "json",
    .flag = "--json",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_key_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_key_side_effects[1] = {
  "write_files",
};
static const char* cmd_yai_substrate_key_law_hooks[1] = {
  "I-001",
};
static const char* cmd_yai_substrate_key_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_substrate_key_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_key_uses_primitives[1] = {
  "S-003",
};
static const yai_law_command_t cmd_yai_substrate_key = {
  .id = "yai.substrate.key",
  .name = "key",
  .group = "substrate",
  .summary = "Key operations (gen/load/fingerprint/sign/verify)",
  .args = cmd_yai_substrate_key_args,
  .args_len = 4,
  .outputs = cmd_yai_substrate_key_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_key_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_substrate_key_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_key_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_key_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_key_uses_primitives,
  .uses_primitives_len = 1,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_hash_arg0_values[4] = {
  "compute",
  "verify",
  "compare",
  "treehash",
};
static const yai_law_arg_t cmd_yai_substrate_hash_args[4] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_hash_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "path",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "expected",
    .flag = "--expected",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "algo",
    .flag = "--algo",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_hash_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_hash_side_effects[1] = {
  "read_files",
};
static const char* cmd_yai_substrate_hash_law_hooks[2] = {
  "I-001",
  "I-002",
};
static const char* cmd_yai_substrate_hash_law_invariants[2] = {
  "I-001-traceability",
  "I-002-determinism",
};
static const char* cmd_yai_substrate_hash_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_hash_uses_primitives[1] = {
  "S-004",
};
static const yai_law_command_t cmd_yai_substrate_hash = {
  .id = "yai.substrate.hash",
  .name = "hash",
  .group = "substrate",
  .summary = "Hash operations (compute/verify/compare/treehash)",
  .args = cmd_yai_substrate_hash_args,
  .args_len = 4,
  .outputs = cmd_yai_substrate_hash_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_hash_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_substrate_hash_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_substrate_hash_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_substrate_hash_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_hash_uses_primitives,
  .uses_primitives_len = 1,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_artifact_arg0_values[5] = {
  "add",
  "inspect",
  "link",
  "verify",
  "gc-mark",
};
static const yai_law_arg_t cmd_yai_substrate_artifact_args[4] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_artifact_arg0_values,
    .values_len = 5,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "path",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "role",
    .flag = "--role",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "store",
    .flag = "--store",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_artifact_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_artifact_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_substrate_artifact_law_hooks[1] = {
  "I-001",
};
static const char* cmd_yai_substrate_artifact_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_substrate_artifact_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_artifact_uses_primitives[4] = {
  "S-005",
  "S-002",
  "S-004",
  "S-006",
};
static const yai_law_command_t cmd_yai_substrate_artifact = {
  .id = "yai.substrate.artifact",
  .name = "artifact",
  .group = "substrate",
  .summary = "Artifact operations (add/inspect/link/verify/gc-mark)",
  .args = cmd_yai_substrate_artifact_args,
  .args_len = 4,
  .outputs = cmd_yai_substrate_artifact_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_artifact_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_substrate_artifact_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_artifact_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_artifact_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_artifact_uses_primitives,
  .uses_primitives_len = 4,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_store_arg0_values[5] = {
  "put",
  "get",
  "list",
  "exists",
  "gc",
};
static const yai_law_arg_t cmd_yai_substrate_store_args[3] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_store_arg0_values,
    .values_len = 5,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "ref",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "path",
    .flag = "--path",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_store_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_store_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_substrate_store_law_hooks[1] = {
  "I-001",
};
static const char* cmd_yai_substrate_store_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_substrate_store_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_store_uses_primitives[3] = {
  "S-006",
  "S-004",
  "S-023",
};
static const yai_law_command_t cmd_yai_substrate_store = {
  .id = "yai.substrate.store",
  .name = "store",
  .group = "substrate",
  .summary = "Store operations (put/get/list/exists/gc)",
  .args = cmd_yai_substrate_store_args,
  .args_len = 3,
  .outputs = cmd_yai_substrate_store_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_store_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_substrate_store_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_store_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_store_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_store_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_schema_arg0_values[4] = {
  "register",
  "show",
  "check",
  "upgrade-map",
};
static const yai_law_arg_t cmd_yai_substrate_schema_args[2] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_schema_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "schema_ref",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_schema_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_schema_side_effects[1] = {
  "read_files",
};
static const char* cmd_yai_substrate_schema_law_hooks[1] = {
  "I-002",
};
static const char* cmd_yai_substrate_schema_law_invariants[1] = {
  "I-002-determinism",
};
static const char* cmd_yai_substrate_schema_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_schema_uses_primitives[1] = {
  "S-007",
};
static const yai_law_command_t cmd_yai_substrate_schema = {
  .id = "yai.substrate.schema",
  .name = "schema",
  .group = "substrate",
  .summary = "Schema operations (register/show/check/upgrade-map)",
  .args = cmd_yai_substrate_schema_args,
  .args_len = 2,
  .outputs = cmd_yai_substrate_schema_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_schema_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_substrate_schema_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_schema_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_schema_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_schema_uses_primitives,
  .uses_primitives_len = 1,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_validate_arg0_values[3] = {
  "validate-schema",
  "validate-set",
  "emit-report",
};
static const yai_law_arg_t cmd_yai_substrate_validate_args[3] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_validate_arg0_values,
    .values_len = 3,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "target",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "out",
    .flag = "--out",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_validate_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_validate_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_substrate_validate_law_hooks[2] = {
  "I-002",
  "I-001",
};
static const char* cmd_yai_substrate_validate_law_invariants[2] = {
  "I-002-determinism",
  "I-001-traceability",
};
static const char* cmd_yai_substrate_validate_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_validate_uses_primitives[4] = {
  "S-008",
  "S-007",
  "S-013",
  "S-014",
};
static const yai_law_command_t cmd_yai_substrate_validate = {
  .id = "yai.substrate.validate",
  .name = "validate",
  .group = "substrate",
  .summary = "Deterministic validation (schema + cross-file)",
  .args = cmd_yai_substrate_validate_args,
  .args_len = 3,
  .outputs = cmd_yai_substrate_validate_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_validate_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_substrate_validate_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_substrate_validate_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_substrate_validate_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_validate_uses_primitives,
  .uses_primitives_len = 4,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_clock_arg0_values[4] = {
  "stamp",
  "normalize",
  "compare",
  "bound",
};
static const yai_law_arg_t cmd_yai_substrate_clock_args[3] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_clock_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "a",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "b",
    .flag = NULL,
    .pos = 3,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_clock_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_clock_law_hooks[1] = {
  "I-002",
};
static const char* cmd_yai_substrate_clock_law_invariants[1] = {
  "I-002-determinism",
};
static const char* cmd_yai_substrate_clock_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_clock_uses_primitives[1] = {
  "S-009",
};
static const yai_law_command_t cmd_yai_substrate_clock = {
  .id = "yai.substrate.clock",
  .name = "clock",
  .group = "substrate",
  .summary = "Clock operations (stamp/normalize/compare/bound)",
  .args = cmd_yai_substrate_clock_args,
  .args_len = 3,
  .outputs = cmd_yai_substrate_clock_outputs,
  .outputs_len = 2,
  .side_effects = NULL,
  .side_effects_len = 0,
  .law_hooks = cmd_yai_substrate_clock_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_clock_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_clock_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_clock_uses_primitives,
  .uses_primitives_len = 1,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_record_arg0_values[4] = {
  "append",
  "read",
  "scan",
  "filter",
};
static const yai_law_arg_t cmd_yai_substrate_record_args[3] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_record_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "path",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "json",
    .flag = "--json",
    .pos = 0,
    .type = "bool",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 1,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_record_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_record_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_substrate_record_law_hooks[1] = {
  "I-001",
};
static const char* cmd_yai_substrate_record_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_substrate_record_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_record_uses_primitives[3] = {
  "S-010",
  "S-004",
  "S-009",
};
static const yai_law_command_t cmd_yai_substrate_record = {
  .id = "yai.substrate.record",
  .name = "record",
  .group = "substrate",
  .summary = "Record operations (append/read/scan/filter)",
  .args = cmd_yai_substrate_record_args,
  .args_len = 3,
  .outputs = cmd_yai_substrate_record_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_record_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_substrate_record_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_record_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_record_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_record_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_timeline_arg0_values[4] = {
  "build",
  "link",
  "check",
  "summarize",
};
static const yai_law_arg_t cmd_yai_substrate_timeline_args[3] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_timeline_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "in",
    .flag = "--in",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "out",
    .flag = "--out",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_timeline_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_timeline_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_substrate_timeline_law_hooks[2] = {
  "I-001",
  "I-002",
};
static const char* cmd_yai_substrate_timeline_law_invariants[2] = {
  "I-001-traceability",
  "I-002-determinism",
};
static const char* cmd_yai_substrate_timeline_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_timeline_uses_primitives[3] = {
  "S-011",
  "S-010",
  "S-004",
};
static const yai_law_command_t cmd_yai_substrate_timeline = {
  .id = "yai.substrate.timeline",
  .name = "timeline",
  .group = "substrate",
  .summary = "Timeline operations (build/link/check/summarize)",
  .args = cmd_yai_substrate_timeline_args,
  .args_len = 3,
  .outputs = cmd_yai_substrate_timeline_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_timeline_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_substrate_timeline_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_substrate_timeline_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_substrate_timeline_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_timeline_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_metrics_arg0_values[4] = {
  "emit",
  "aggregate",
  "rollup",
  "diff",
};
static const yai_law_arg_t cmd_yai_substrate_metrics_args[3] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_metrics_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "in",
    .flag = "--in",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "out",
    .flag = "--out",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_metrics_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_metrics_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_substrate_metrics_law_hooks[1] = {
  "I-001",
};
static const char* cmd_yai_substrate_metrics_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_substrate_metrics_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_metrics_uses_primitives[2] = {
  "S-012",
  "S-010",
};
static const yai_law_command_t cmd_yai_substrate_metrics = {
  .id = "yai.substrate.metrics",
  .name = "metrics",
  .group = "substrate",
  .summary = "Metric operations (emit/aggregate/rollup/diff)",
  .args = cmd_yai_substrate_metrics_args,
  .args_len = 3,
  .outputs = cmd_yai_substrate_metrics_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_metrics_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_substrate_metrics_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_metrics_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_metrics_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_metrics_uses_primitives,
  .uses_primitives_len = 2,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_index_arg0_values[4] = {
  "build",
  "update",
  "verify",
  "materialize",
};
static const yai_law_arg_t cmd_yai_substrate_index_args[2] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_index_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "root",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_index_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_index_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_substrate_index_law_hooks[1] = {
  "I-001",
};
static const char* cmd_yai_substrate_index_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_substrate_index_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_index_uses_primitives[3] = {
  "S-013",
  "S-005",
  "S-004",
};
static const yai_law_artifact_io_t cmd_yai_substrate_index_emits_artifacts[1] = {
  {
    .role = "evidence_index",
    .schema_ref = "schema/evidence_index.v1.schema.json",
    .path_hint = "evidence_index.json",
  },
};
static const yai_law_command_t cmd_yai_substrate_index = {
  .id = "yai.substrate.index",
  .name = "index",
  .group = "substrate",
  .summary = "Index operations (build/update/verify/materialize)",
  .args = cmd_yai_substrate_index_args,
  .args_len = 2,
  .outputs = cmd_yai_substrate_index_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_index_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_substrate_index_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_index_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_index_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_index_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = cmd_yai_substrate_index_emits_artifacts,
  .emits_artifacts_len = 1,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_manifest_arg0_values[4] = {
  "compose",
  "seal",
  "verify",
  "diff",
};
static const yai_law_arg_t cmd_yai_substrate_manifest_args[2] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_manifest_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "root",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_manifest_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_manifest_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_substrate_manifest_law_hooks[2] = {
  "I-001",
  "I-002",
};
static const char* cmd_yai_substrate_manifest_law_invariants[2] = {
  "I-001-traceability",
  "I-002-determinism",
};
static const char* cmd_yai_substrate_manifest_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_manifest_uses_primitives[3] = {
  "S-014",
  "S-013",
  "S-004",
};
static const yai_law_artifact_io_t cmd_yai_substrate_manifest_emits_artifacts[1] = {
  {
    .role = "bundle_manifest",
    .schema_ref = "schema/bundle_manifest.v1.schema.json",
    .path_hint = "bundle_manifest.json",
  },
};
static const yai_law_command_t cmd_yai_substrate_manifest = {
  .id = "yai.substrate.manifest",
  .name = "manifest",
  .group = "substrate",
  .summary = "Manifest operations (compose/seal/verify/diff)",
  .args = cmd_yai_substrate_manifest_args,
  .args_len = 2,
  .outputs = cmd_yai_substrate_manifest_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_manifest_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_substrate_manifest_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_substrate_manifest_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_substrate_manifest_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_manifest_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = cmd_yai_substrate_manifest_emits_artifacts,
  .emits_artifacts_len = 1,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_select_arg0_values[4] = {
  "select",
  "explain",
  "replay",
  "lock",
};
static const yai_law_arg_t cmd_yai_substrate_select_args[2] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_select_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "selector",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_select_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_select_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_substrate_select_law_hooks[1] = {
  "I-002",
};
static const char* cmd_yai_substrate_select_law_invariants[1] = {
  "I-002-determinism",
};
static const char* cmd_yai_substrate_select_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_select_uses_primitives[3] = {
  "S-015",
  "S-010",
  "S-013",
};
static const yai_law_command_t cmd_yai_substrate_select = {
  .id = "yai.substrate.select",
  .name = "select",
  .group = "substrate",
  .summary = "Selector operations (select/explain/replay/lock)",
  .args = cmd_yai_substrate_select_args,
  .args_len = 2,
  .outputs = cmd_yai_substrate_select_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_select_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_substrate_select_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_select_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_select_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_select_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_channel_arg0_values[4] = {
  "open",
  "write",
  "tail",
  "export",
};
static const yai_law_arg_t cmd_yai_substrate_channel_args[2] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_channel_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "target",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_channel_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_channel_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_substrate_channel_law_hooks[1] = {
  "I-001",
};
static const char* cmd_yai_substrate_channel_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_substrate_channel_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_channel_uses_primitives[1] = {
  "S-016",
};
static const yai_law_command_t cmd_yai_substrate_channel = {
  .id = "yai.substrate.channel",
  .name = "channel",
  .group = "substrate",
  .summary = "Channel operations (open/write/tail/export)",
  .args = cmd_yai_substrate_channel_args,
  .args_len = 2,
  .outputs = cmd_yai_substrate_channel_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_channel_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_substrate_channel_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_channel_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_channel_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_channel_uses_primitives,
  .uses_primitives_len = 1,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_env_arg0_values[4] = {
  "capture",
  "hash",
  "diff",
  "assert",
};
static const yai_law_arg_t cmd_yai_substrate_env_args[2] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_env_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "out",
    .flag = "--out",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_env_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_env_side_effects[1] = {
  "write_files",
};
static const char* cmd_yai_substrate_env_law_hooks[1] = {
  "I-001",
};
static const char* cmd_yai_substrate_env_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_substrate_env_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_env_uses_primitives[2] = {
  "S-017",
  "S-004",
};
static const yai_law_command_t cmd_yai_substrate_env = {
  .id = "yai.substrate.env",
  .name = "env",
  .group = "substrate",
  .summary = "Environment fingerprint (capture/hash/diff/assert)",
  .args = cmd_yai_substrate_env_args,
  .args_len = 2,
  .outputs = cmd_yai_substrate_env_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_env_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_substrate_env_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_env_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_env_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_env_uses_primitives,
  .uses_primitives_len = 2,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_compat_arg0_values[4] = {
  "classify",
  "check",
  "negotiate",
  "deprecate",
};
static const yai_law_arg_t cmd_yai_substrate_compat_args[3] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_compat_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "a",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "b",
    .flag = NULL,
    .pos = 3,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_compat_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_compat_law_hooks[1] = {
  "I-002",
};
static const char* cmd_yai_substrate_compat_law_invariants[1] = {
  "I-002-determinism",
};
static const char* cmd_yai_substrate_compat_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_compat_uses_primitives[1] = {
  "S-018",
};
static const yai_law_command_t cmd_yai_substrate_compat = {
  .id = "yai.substrate.compat",
  .name = "compat",
  .group = "substrate",
  .summary = "Compatibility/versioning (classify/check/negotiate/deprecate)",
  .args = cmd_yai_substrate_compat_args,
  .args_len = 3,
  .outputs = cmd_yai_substrate_compat_outputs,
  .outputs_len = 2,
  .side_effects = NULL,
  .side_effects_len = 0,
  .law_hooks = cmd_yai_substrate_compat_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_compat_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_compat_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_compat_uses_primitives,
  .uses_primitives_len = 1,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_fs_arg0_values[3] = {
  "path",
  "file",
  "dir",
};
static const yai_law_arg_t cmd_yai_substrate_fs_args[3] = {
  {
    .name = "subsystem",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_fs_arg0_values,
    .values_len = 3,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "op",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "target",
    .flag = NULL,
    .pos = 3,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_fs_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_fs_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_substrate_fs_law_hooks[2] = {
  "I-006",
  "I-001",
};
static const char* cmd_yai_substrate_fs_law_invariants[2] = {
  "I-006-external-effect-boundary",
  "I-001-traceability",
};
static const char* cmd_yai_substrate_fs_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_fs_uses_primitives[3] = {
  "S-019",
  "S-020",
  "S-021",
};
static const yai_law_command_t cmd_yai_substrate_fs = {
  .id = "yai.substrate.fs",
  .name = "fs",
  .group = "substrate",
  .summary = "Filesystem ops (path/file/dir)",
  .args = cmd_yai_substrate_fs_args,
  .args_len = 3,
  .outputs = cmd_yai_substrate_fs_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_fs_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_substrate_fs_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_substrate_fs_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_substrate_fs_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_fs_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_stream_arg0_values[5] = {
  "open",
  "push",
  "pull",
  "flush",
  "close",
};
static const yai_law_arg_t cmd_yai_substrate_stream_args[2] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_stream_arg0_values,
    .values_len = 5,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "target",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_stream_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_stream_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_substrate_stream_law_hooks[1] = {
  "I-001",
};
static const char* cmd_yai_substrate_stream_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_substrate_stream_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_stream_uses_primitives[1] = {
  "S-022",
};
static const yai_law_command_t cmd_yai_substrate_stream = {
  .id = "yai.substrate.stream",
  .name = "stream",
  .group = "substrate",
  .summary = "Stream ops (open/push/pull/flush/close)",
  .args = cmd_yai_substrate_stream_args,
  .args_len = 2,
  .outputs = cmd_yai_substrate_stream_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_stream_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_substrate_stream_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_stream_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_stream_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_stream_uses_primitives,
  .uses_primitives_len = 1,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_lock_arg0_values[4] = {
  "acquire",
  "release",
  "try",
  "assert-held",
};
static const yai_law_arg_t cmd_yai_substrate_lock_args[2] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_lock_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "name",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_lock_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_lock_side_effects[1] = {
  "write_files",
};
static const char* cmd_yai_substrate_lock_law_hooks[1] = {
  "I-002",
};
static const char* cmd_yai_substrate_lock_law_invariants[1] = {
  "I-002-determinism",
};
static const char* cmd_yai_substrate_lock_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_lock_uses_primitives[1] = {
  "S-023",
};
static const yai_law_command_t cmd_yai_substrate_lock = {
  .id = "yai.substrate.lock",
  .name = "lock",
  .group = "substrate",
  .summary = "Lock ops (acquire/release/try/assert-held)",
  .args = cmd_yai_substrate_lock_args,
  .args_len = 2,
  .outputs = cmd_yai_substrate_lock_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_lock_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_substrate_lock_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_lock_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_lock_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_lock_uses_primitives,
  .uses_primitives_len = 1,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_txn_arg0_values[4] = {
  "begin",
  "stage",
  "commit",
  "rollback",
};
static const yai_law_arg_t cmd_yai_substrate_txn_args[2] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_txn_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "target",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_txn_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_txn_side_effects[1] = {
  "write_files",
};
static const char* cmd_yai_substrate_txn_law_hooks[2] = {
  "I-001",
  "I-002",
};
static const char* cmd_yai_substrate_txn_law_invariants[2] = {
  "I-001-traceability",
  "I-002-determinism",
};
static const char* cmd_yai_substrate_txn_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_txn_uses_primitives[3] = {
  "S-024",
  "S-023",
  "S-006",
};
static const yai_law_command_t cmd_yai_substrate_txn = {
  .id = "yai.substrate.txn",
  .name = "txn",
  .group = "substrate",
  .summary = "Transaction ops (begin/stage/commit/rollback)",
  .args = cmd_yai_substrate_txn_args,
  .args_len = 2,
  .outputs = cmd_yai_substrate_txn_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_txn_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_substrate_txn_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_substrate_txn_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_substrate_txn_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_txn_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_error_arg0_values[4] = {
  "raise",
  "wrap",
  "classify",
  "render",
};
static const yai_law_arg_t cmd_yai_substrate_error_args[2] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_error_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "code",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_error_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_error_law_hooks[1] = {
  "I-001",
};
static const char* cmd_yai_substrate_error_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_substrate_error_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_error_uses_primitives[1] = {
  "S-025",
};
static const yai_law_command_t cmd_yai_substrate_error = {
  .id = "yai.substrate.error",
  .name = "error",
  .group = "substrate",
  .summary = "Error ops (raise/wrap/classify/render)",
  .args = cmd_yai_substrate_error_args,
  .args_len = 2,
  .outputs = cmd_yai_substrate_error_outputs,
  .outputs_len = 2,
  .side_effects = NULL,
  .side_effects_len = 0,
  .law_hooks = cmd_yai_substrate_error_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_error_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_error_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_error_uses_primitives,
  .uses_primitives_len = 1,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_resource_arg0_values[4] = {
  "measure",
  "allocate",
  "release",
  "cap",
};
static const yai_law_arg_t cmd_yai_substrate_resource_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_resource_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_resource_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_resource_side_effects[1] = {
  "read_system",
};
static const char* cmd_yai_substrate_resource_law_hooks[1] = {
  "I-001",
};
static const char* cmd_yai_substrate_resource_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_substrate_resource_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_resource_uses_primitives[1] = {
  "S-027",
};
static const yai_law_command_t cmd_yai_substrate_resource = {
  .id = "yai.substrate.resource",
  .name = "resource",
  .group = "substrate",
  .summary = "Resource ops (measure/allocate/release/cap)",
  .args = cmd_yai_substrate_resource_args,
  .args_len = 1,
  .outputs = cmd_yai_substrate_resource_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_resource_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_substrate_resource_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_resource_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_resource_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_resource_uses_primitives,
  .uses_primitives_len = 1,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_quota_arg0_values[4] = {
  "set",
  "enforce",
  "report",
  "diff",
};
static const yai_law_arg_t cmd_yai_substrate_quota_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_quota_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_quota_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_quota_side_effects[1] = {
  "write_files",
};
static const char* cmd_yai_substrate_quota_law_hooks[1] = {
  "I-005",
};
static const char* cmd_yai_substrate_quota_law_invariants[1] = {
  "I-005-abstract-cost-accountability",
};
static const char* cmd_yai_substrate_quota_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_quota_uses_primitives[2] = {
  "S-028",
  "S-027",
};
static const yai_law_command_t cmd_yai_substrate_quota = {
  .id = "yai.substrate.quota",
  .name = "quota",
  .group = "substrate",
  .summary = "Quota ops (set/enforce/report/diff)",
  .args = cmd_yai_substrate_quota_args,
  .args_len = 1,
  .outputs = cmd_yai_substrate_quota_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_quota_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_substrate_quota_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_quota_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_quota_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_quota_uses_primitives,
  .uses_primitives_len = 2,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_sandbox_arg0_values[4] = {
  "create",
  "enter",
  "enforce",
  "inspect",
};
static const yai_law_arg_t cmd_yai_substrate_sandbox_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_sandbox_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_sandbox_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_sandbox_side_effects[1] = {
  "spawn_processes",
};
static const char* cmd_yai_substrate_sandbox_law_hooks[1] = {
  "I-006",
};
static const char* cmd_yai_substrate_sandbox_law_invariants[1] = {
  "I-006-external-effect-boundary",
};
static const char* cmd_yai_substrate_sandbox_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_sandbox_uses_primitives[2] = {
  "S-029",
  "S-028",
};
static const yai_law_command_t cmd_yai_substrate_sandbox = {
  .id = "yai.substrate.sandbox",
  .name = "sandbox",
  .group = "substrate",
  .summary = "Sandbox ops (create/enter/enforce/inspect)",
  .args = cmd_yai_substrate_sandbox_args,
  .args_len = 1,
  .outputs = cmd_yai_substrate_sandbox_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_sandbox_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_substrate_sandbox_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_sandbox_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_sandbox_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_sandbox_uses_primitives,
  .uses_primitives_len = 2,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_cap_arg0_values[4] = {
  "declare",
  "assert",
  "list",
  "deny",
};
static const yai_law_arg_t cmd_yai_substrate_cap_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_cap_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_cap_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_cap_law_hooks[1] = {
  "I-003",
};
static const char* cmd_yai_substrate_cap_law_invariants[1] = {
  "I-003-governance",
};
static const char* cmd_yai_substrate_cap_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_cap_uses_primitives[2] = {
  "S-030",
  "S-029",
};
static const yai_law_command_t cmd_yai_substrate_cap = {
  .id = "yai.substrate.cap",
  .name = "cap",
  .group = "substrate",
  .summary = "Capability ops (declare/assert/list/deny)",
  .args = cmd_yai_substrate_cap_args,
  .args_len = 1,
  .outputs = cmd_yai_substrate_cap_outputs,
  .outputs_len = 2,
  .side_effects = NULL,
  .side_effects_len = 0,
  .law_hooks = cmd_yai_substrate_cap_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_cap_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_cap_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_cap_uses_primitives,
  .uses_primitives_len = 2,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_net_arg0_values[2] = {
  "endpoint",
  "route",
};
static const yai_law_arg_t cmd_yai_substrate_net_args[3] = {
  {
    .name = "subsystem",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_net_arg0_values,
    .values_len = 2,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "op",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "value",
    .flag = NULL,
    .pos = 3,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_net_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_net_side_effects[1] = {
  "network",
};
static const char* cmd_yai_substrate_net_law_hooks[2] = {
  "I-006",
  "I-001",
};
static const char* cmd_yai_substrate_net_law_invariants[2] = {
  "I-006-external-effect-boundary",
  "I-001-traceability",
};
static const char* cmd_yai_substrate_net_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_net_uses_primitives[2] = {
  "S-031",
  "S-032",
};
static const yai_law_command_t cmd_yai_substrate_net = {
  .id = "yai.substrate.net",
  .name = "net",
  .group = "substrate",
  .summary = "Network ops (endpoint/route)",
  .args = cmd_yai_substrate_net_args,
  .args_len = 3,
  .outputs = cmd_yai_substrate_net_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_net_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_substrate_net_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_substrate_net_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_substrate_net_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_net_uses_primitives,
  .uses_primitives_len = 2,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_codec_arg0_values[4] = {
  "encode",
  "decode",
  "sniff",
  "assert",
};
static const yai_law_arg_t cmd_yai_substrate_codec_args[3] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_codec_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "in",
    .flag = "--in",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "out",
    .flag = "--out",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_codec_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_codec_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_substrate_codec_law_hooks[1] = {
  "I-002",
};
static const char* cmd_yai_substrate_codec_law_invariants[1] = {
  "I-002-determinism",
};
static const char* cmd_yai_substrate_codec_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_codec_uses_primitives[1] = {
  "S-033",
};
static const yai_law_command_t cmd_yai_substrate_codec = {
  .id = "yai.substrate.codec",
  .name = "codec",
  .group = "substrate",
  .summary = "Codec ops (encode/decode/sniff/assert)",
  .args = cmd_yai_substrate_codec_args,
  .args_len = 3,
  .outputs = cmd_yai_substrate_codec_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_codec_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_substrate_codec_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_codec_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_codec_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_codec_uses_primitives,
  .uses_primitives_len = 1,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_seed_arg0_values[4] = {
  "set",
  "get",
  "derive",
  "record",
};
static const yai_law_arg_t cmd_yai_substrate_seed_args[2] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_seed_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "value",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_seed_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_seed_side_effects[1] = {
  "write_files",
};
static const char* cmd_yai_substrate_seed_law_hooks[1] = {
  "I-002",
};
static const char* cmd_yai_substrate_seed_law_invariants[1] = {
  "I-002-determinism",
};
static const char* cmd_yai_substrate_seed_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_seed_uses_primitives[1] = {
  "S-034",
};
static const yai_law_command_t cmd_yai_substrate_seed = {
  .id = "yai.substrate.seed",
  .name = "seed",
  .group = "substrate",
  .summary = "Seed ops (set/get/derive/record)",
  .args = cmd_yai_substrate_seed_args,
  .args_len = 2,
  .outputs = cmd_yai_substrate_seed_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_seed_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_substrate_seed_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_seed_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_seed_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_seed_uses_primitives,
  .uses_primitives_len = 1,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_prov_arg0_values[4] = {
  "record",
  "link",
  "query",
  "render",
};
static const yai_law_arg_t cmd_yai_substrate_prov_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_prov_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_prov_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_prov_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_substrate_prov_law_hooks[1] = {
  "I-001",
};
static const char* cmd_yai_substrate_prov_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_substrate_prov_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_prov_uses_primitives[4] = {
  "S-035",
  "S-002",
  "S-010",
  "S-005",
};
static const yai_law_command_t cmd_yai_substrate_prov = {
  .id = "yai.substrate.prov",
  .name = "prov",
  .group = "substrate",
  .summary = "Provenance ops (record/link/query/render)",
  .args = cmd_yai_substrate_prov_args,
  .args_len = 1,
  .outputs = cmd_yai_substrate_prov_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_prov_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_substrate_prov_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_prov_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_prov_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_prov_uses_primitives,
  .uses_primitives_len = 4,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_journal_arg0_values[4] = {
  "append",
  "rotate",
  "verify",
  "export",
};
static const yai_law_arg_t cmd_yai_substrate_journal_args[2] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_journal_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "path",
    .flag = "--path",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_journal_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_journal_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_substrate_journal_law_hooks[1] = {
  "I-001",
};
static const char* cmd_yai_substrate_journal_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_substrate_journal_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_journal_uses_primitives[2] = {
  "S-041",
  "S-010",
};
static const yai_law_command_t cmd_yai_substrate_journal = {
  .id = "yai.substrate.journal",
  .name = "journal",
  .group = "substrate",
  .summary = "Journal ops (append/rotate/verify/export)",
  .args = cmd_yai_substrate_journal_args,
  .args_len = 2,
  .outputs = cmd_yai_substrate_journal_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_journal_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_substrate_journal_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_journal_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_journal_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_journal_uses_primitives,
  .uses_primitives_len = 2,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_checkpoint_arg0_values[4] = {
  "create",
  "restore",
  "list",
  "prune",
};
static const yai_law_arg_t cmd_yai_substrate_checkpoint_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_checkpoint_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_checkpoint_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_checkpoint_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_substrate_checkpoint_law_hooks[1] = {
  "I-002",
};
static const char* cmd_yai_substrate_checkpoint_law_invariants[1] = {
  "I-002-determinism",
};
static const char* cmd_yai_substrate_checkpoint_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_checkpoint_uses_primitives[3] = {
  "S-042",
  "S-006",
  "S-023",
};
static const yai_law_command_t cmd_yai_substrate_checkpoint = {
  .id = "yai.substrate.checkpoint",
  .name = "checkpoint",
  .group = "substrate",
  .summary = "Checkpoint ops (create/restore/list/prune)",
  .args = cmd_yai_substrate_checkpoint_args,
  .args_len = 1,
  .outputs = cmd_yai_substrate_checkpoint_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_checkpoint_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_substrate_checkpoint_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_checkpoint_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_checkpoint_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_checkpoint_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_diff_arg0_values[3] = {
  "diff",
  "summarize",
  "classify",
};
static const yai_law_arg_t cmd_yai_substrate_diff_args[3] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_diff_arg0_values,
    .values_len = 3,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "a",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "b",
    .flag = NULL,
    .pos = 3,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_diff_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_diff_side_effects[1] = {
  "read_files",
};
static const char* cmd_yai_substrate_diff_law_hooks[1] = {
  "I-001",
};
static const char* cmd_yai_substrate_diff_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_substrate_diff_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_diff_uses_primitives[3] = {
  "S-043",
  "S-004",
  "S-013",
};
static const yai_law_command_t cmd_yai_substrate_diff = {
  .id = "yai.substrate.diff",
  .name = "diff",
  .group = "substrate",
  .summary = "Diff ops (diff/summarize/classify)",
  .args = cmd_yai_substrate_diff_args,
  .args_len = 3,
  .outputs = cmd_yai_substrate_diff_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_diff_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_substrate_diff_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_substrate_diff_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_substrate_diff_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_diff_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_substrate_patch_arg0_values[3] = {
  "apply",
  "verify",
  "rollback",
};
static const yai_law_arg_t cmd_yai_substrate_patch_args[2] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_substrate_patch_arg0_values,
    .values_len = 3,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "patch",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_substrate_patch_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_substrate_patch_side_effects[1] = {
  "write_files",
};
static const char* cmd_yai_substrate_patch_law_hooks[2] = {
  "I-001",
  "I-006",
};
static const char* cmd_yai_substrate_patch_law_invariants[2] = {
  "I-001-traceability",
  "I-006-external-effect-boundary",
};
static const char* cmd_yai_substrate_patch_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_substrate_patch_uses_primitives[3] = {
  "S-044",
  "S-024",
  "S-041",
};
static const yai_law_command_t cmd_yai_substrate_patch = {
  .id = "yai.substrate.patch",
  .name = "patch",
  .group = "substrate",
  .summary = "Patch ops (apply/verify/rollback)",
  .args = cmd_yai_substrate_patch_args,
  .args_len = 2,
  .outputs = cmd_yai_substrate_patch_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_substrate_patch_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_substrate_patch_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_substrate_patch_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_substrate_patch_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_substrate_patch_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_governance_event_arg0_values[4] = {
  "emit",
  "classify",
  "link",
  "ingest",
};
static const yai_law_arg_t cmd_yai_governance_event_args[2] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_governance_event_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "in",
    .flag = "--in",
    .pos = 0,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_governance_event_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_governance_event_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_governance_event_law_hooks[1] = {
  "I-001",
};
static const char* cmd_yai_governance_event_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_governance_event_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_governance_event_uses_primitives[4] = {
  "T-001",
  "S-010",
  "S-009",
  "S-002",
};
static const yai_law_command_t cmd_yai_governance_event = {
  .id = "yai.governance.event",
  .name = "event",
  .group = "governance",
  .summary = "Governance event ops (emit/classify/link/ingest)",
  .args = cmd_yai_governance_event_args,
  .args_len = 2,
  .outputs = cmd_yai_governance_event_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_governance_event_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_governance_event_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_governance_event_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_governance_event_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_governance_event_uses_primitives,
  .uses_primitives_len = 4,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_governance_identity_arg0_values[4] = {
  "bind",
  "resolve",
  "attest",
  "alias",
};
static const yai_law_arg_t cmd_yai_governance_identity_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_governance_identity_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_governance_identity_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_governance_identity_side_effects[1] = {
  "write_files",
};
static const char* cmd_yai_governance_identity_law_hooks[1] = {
  "I-001",
};
static const char* cmd_yai_governance_identity_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_governance_identity_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_governance_identity_uses_primitives[3] = {
  "T-002",
  "S-002",
  "S-003",
};
static const yai_law_command_t cmd_yai_governance_identity = {
  .id = "yai.governance.identity",
  .name = "identity",
  .group = "governance",
  .summary = "Identity ops (bind/resolve/attest/alias)",
  .args = cmd_yai_governance_identity_args,
  .args_len = 1,
  .outputs = cmd_yai_governance_identity_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_governance_identity_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_governance_identity_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_governance_identity_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_governance_identity_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_governance_identity_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_governance_authority_arg0_values[4] = {
  "request",
  "evaluate",
  "grant-deny",
  "audit",
};
static const yai_law_arg_t cmd_yai_governance_authority_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_governance_authority_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_governance_authority_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_governance_authority_side_effects[2] = {
  "rpc_call",
  "write_files",
};
static const char* cmd_yai_governance_authority_law_hooks[2] = {
  "I-003",
  "I-001",
};
static const char* cmd_yai_governance_authority_law_invariants[2] = {
  "I-003-governance",
  "I-001-traceability",
};
static const char* cmd_yai_governance_authority_law_boundaries[3] = {
  "L1-kernel",
  "L2-engine",
  "L3-mind",
};
static const char* cmd_yai_governance_authority_uses_primitives[3] = {
  "T-003",
  "T-021",
  "S-002",
};
static const yai_law_command_t cmd_yai_governance_authority = {
  .id = "yai.governance.authority",
  .name = "authority",
  .group = "governance",
  .summary = "Authority ops (request/evaluate/grant-deny/audit)",
  .args = cmd_yai_governance_authority_args,
  .args_len = 1,
  .outputs = cmd_yai_governance_authority_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_governance_authority_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_governance_authority_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_governance_authority_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_governance_authority_law_boundaries,
  .law_boundaries_len = 3,
  .uses_primitives = cmd_yai_governance_authority_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_governance_contract_arg0_values[4] = {
  "define",
  "reference",
  "test",
  "deprecate",
};
static const yai_law_arg_t cmd_yai_governance_contract_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_governance_contract_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_governance_contract_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_governance_contract_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_governance_contract_law_hooks[1] = {
  "I-003",
};
static const char* cmd_yai_governance_contract_law_invariants[1] = {
  "I-003-governance",
};
static const char* cmd_yai_governance_contract_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_governance_contract_uses_primitives[3] = {
  "T-004",
  "S-001",
  "S-007",
};
static const yai_law_command_t cmd_yai_governance_contract = {
  .id = "yai.governance.contract",
  .name = "contract",
  .group = "governance",
  .summary = "Contract ops (define/reference/test/deprecate)",
  .args = cmd_yai_governance_contract_args,
  .args_len = 1,
  .outputs = cmd_yai_governance_contract_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_governance_contract_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_governance_contract_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_governance_contract_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_governance_contract_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_governance_contract_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_governance_baseline_arg0_values[4] = {
  "select",
  "pin",
  "hash",
  "audit",
};
static const yai_law_arg_t cmd_yai_governance_baseline_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_governance_baseline_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_governance_baseline_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_governance_baseline_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_governance_baseline_law_hooks[2] = {
  "I-002",
  "I-003",
};
static const char* cmd_yai_governance_baseline_law_invariants[2] = {
  "I-002-determinism",
  "I-003-governance",
};
static const char* cmd_yai_governance_baseline_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_governance_baseline_uses_primitives[3] = {
  "T-005",
  "T-004",
  "S-004",
};
static const yai_law_command_t cmd_yai_governance_baseline = {
  .id = "yai.governance.baseline",
  .name = "baseline",
  .group = "governance",
  .summary = "Baseline ops (select/pin/hash/audit)",
  .args = cmd_yai_governance_baseline_args,
  .args_len = 1,
  .outputs = cmd_yai_governance_baseline_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_governance_baseline_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_governance_baseline_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_governance_baseline_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_governance_baseline_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_governance_baseline_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_governance_policy_arg0_values[4] = {
  "load",
  "hash",
  "evaluate",
  "pin",
};
static const yai_law_arg_t cmd_yai_governance_policy_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_governance_policy_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_governance_policy_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_governance_policy_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_governance_policy_law_hooks[2] = {
  "I-003",
  "I-001",
};
static const char* cmd_yai_governance_policy_law_invariants[2] = {
  "I-003-governance",
  "I-001-traceability",
};
static const char* cmd_yai_governance_policy_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_governance_policy_uses_primitives[5] = {
  "T-006",
  "T-004",
  "T-005",
  "S-004",
  "S-007",
};
static const yai_law_artifact_io_t cmd_yai_governance_policy_emits_artifacts[1] = {
  {
    .role = "policy",
    .schema_ref = "schema/policy.v1.schema.json",
    .path_hint = "policy.v1.json",
  },
};
static const yai_law_command_t cmd_yai_governance_policy = {
  .id = "yai.governance.policy",
  .name = "policy",
  .group = "governance",
  .summary = "Policy ops (load/hash/evaluate/pin)",
  .args = cmd_yai_governance_policy_args,
  .args_len = 1,
  .outputs = cmd_yai_governance_policy_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_governance_policy_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_governance_policy_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_governance_policy_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_governance_policy_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_governance_policy_uses_primitives,
  .uses_primitives_len = 5,
  .emits_artifacts = cmd_yai_governance_policy_emits_artifacts,
  .emits_artifacts_len = 1,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_governance_decision_arg0_values[4] = {
  "make",
  "record",
  "link",
  "explain",
};
static const yai_law_arg_t cmd_yai_governance_decision_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_governance_decision_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_governance_decision_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_governance_decision_side_effects[1] = {
  "write_files",
};
static const char* cmd_yai_governance_decision_law_hooks[2] = {
  "I-001",
  "I-003",
};
static const char* cmd_yai_governance_decision_law_invariants[2] = {
  "I-001-traceability",
  "I-003-governance",
};
static const char* cmd_yai_governance_decision_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_governance_decision_uses_primitives[5] = {
  "T-007",
  "T-001",
  "T-006",
  "T-003",
  "S-010",
};
static const yai_law_artifact_io_t cmd_yai_governance_decision_emits_artifacts[1] = {
  {
    .role = "decision_record",
    .schema_ref = "schema/decision_record.v1.schema.json",
    .path_hint = "decision_record.jsonl",
  },
};
static const yai_law_command_t cmd_yai_governance_decision = {
  .id = "yai.governance.decision",
  .name = "decision",
  .group = "governance",
  .summary = "Decision ops (make/record/link/explain)",
  .args = cmd_yai_governance_decision_args,
  .args_len = 1,
  .outputs = cmd_yai_governance_decision_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_governance_decision_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_governance_decision_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_governance_decision_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_governance_decision_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_governance_decision_uses_primitives,
  .uses_primitives_len = 5,
  .emits_artifacts = cmd_yai_governance_decision_emits_artifacts,
  .emits_artifacts_len = 1,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_governance_reason_arg0_values[3] = {
  "assign",
  "catalog",
  "aggregate",
};
static const yai_law_arg_t cmd_yai_governance_reason_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_governance_reason_arg0_values,
    .values_len = 3,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_governance_reason_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_governance_reason_law_hooks[1] = {
  "I-001",
};
static const char* cmd_yai_governance_reason_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_governance_reason_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_governance_reason_uses_primitives[2] = {
  "T-009",
  "S-001",
};
static const yai_law_command_t cmd_yai_governance_reason = {
  .id = "yai.governance.reason",
  .name = "reason",
  .group = "governance",
  .summary = "ReasonCode ops (assign/catalog/aggregate)",
  .args = cmd_yai_governance_reason_args,
  .args_len = 1,
  .outputs = cmd_yai_governance_reason_outputs,
  .outputs_len = 2,
  .side_effects = NULL,
  .side_effects_len = 0,
  .law_hooks = cmd_yai_governance_reason_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_governance_reason_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_governance_reason_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_governance_reason_uses_primitives,
  .uses_primitives_len = 2,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_governance_effect_arg0_values[4] = {
  "attempt",
  "apply",
  "measure",
  "record",
};
static const yai_law_arg_t cmd_yai_governance_effect_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_governance_effect_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_governance_effect_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_governance_effect_side_effects[2] = {
  "network",
  "write_files",
};
static const char* cmd_yai_governance_effect_law_hooks[3] = {
  "I-006",
  "I-007",
  "I-001",
};
static const char* cmd_yai_governance_effect_law_invariants[3] = {
  "I-006-external-effect-boundary",
  "I-007-compliance-context-required",
  "I-001-traceability",
};
static const char* cmd_yai_governance_effect_law_boundaries[3] = {
  "L1-kernel",
  "L2-engine",
  "L3-mind",
};
static const char* cmd_yai_governance_effect_uses_primitives[3] = {
  "T-010",
  "T-007",
  "S-010",
};
static const yai_law_command_t cmd_yai_governance_effect = {
  .id = "yai.governance.effect",
  .name = "effect",
  .group = "governance",
  .summary = "Effect ops (attempt/apply/measure/record)",
  .args = cmd_yai_governance_effect_args,
  .args_len = 1,
  .outputs = cmd_yai_governance_effect_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_governance_effect_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_governance_effect_law_hooks,
  .law_hooks_len = 3,
  .law_invariants = cmd_yai_governance_effect_law_invariants,
  .law_invariants_len = 3,
  .law_boundaries = cmd_yai_governance_effect_law_boundaries,
  .law_boundaries_len = 3,
  .uses_primitives = cmd_yai_governance_effect_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_governance_evidence_arg0_values[4] = {
  "collect",
  "curate",
  "hash",
  "index",
};
static const yai_law_arg_t cmd_yai_governance_evidence_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_governance_evidence_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_governance_evidence_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_governance_evidence_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_governance_evidence_law_hooks[1] = {
  "I-001",
};
static const char* cmd_yai_governance_evidence_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_governance_evidence_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_governance_evidence_uses_primitives[4] = {
  "T-011",
  "S-005",
  "S-013",
  "S-004",
};
static const yai_law_artifact_io_t cmd_yai_governance_evidence_emits_artifacts[1] = {
  {
    .role = "evidence_index",
    .schema_ref = "schema/evidence_index.v1.schema.json",
    .path_hint = "evidence_index.json",
  },
};
static const yai_law_command_t cmd_yai_governance_evidence = {
  .id = "yai.governance.evidence",
  .name = "evidence",
  .group = "governance",
  .summary = "Evidence ops (collect/curate/hash/index)",
  .args = cmd_yai_governance_evidence_args,
  .args_len = 1,
  .outputs = cmd_yai_governance_evidence_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_governance_evidence_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_governance_evidence_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_governance_evidence_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_governance_evidence_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_governance_evidence_uses_primitives,
  .uses_primitives_len = 4,
  .emits_artifacts = cmd_yai_governance_evidence_emits_artifacts,
  .emits_artifacts_len = 1,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_governance_run_arg0_values[4] = {
  "start",
  "end",
  "emit",
  "validate",
};
static const yai_law_arg_t cmd_yai_governance_run_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_governance_run_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_governance_run_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_governance_run_side_effects[1] = {
  "write_files",
};
static const char* cmd_yai_governance_run_law_hooks[2] = {
  "I-001",
  "I-002",
};
static const char* cmd_yai_governance_run_law_invariants[2] = {
  "I-001-traceability",
  "I-002-determinism",
};
static const char* cmd_yai_governance_run_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_governance_run_uses_primitives[5] = {
  "T-012",
  "S-010",
  "S-013",
  "S-014",
  "S-017",
};
static const yai_law_command_t cmd_yai_governance_run = {
  .id = "yai.governance.run",
  .name = "run",
  .group = "governance",
  .summary = "Run ops (start/end/emit/validate)",
  .args = cmd_yai_governance_run_args,
  .args_len = 1,
  .outputs = cmd_yai_governance_run_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_governance_run_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_governance_run_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_governance_run_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_governance_run_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_governance_run_uses_primitives,
  .uses_primitives_len = 5,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_governance_wave_arg0_values[4] = {
  "plan",
  "execute",
  "select",
  "summarize",
};
static const yai_law_arg_t cmd_yai_governance_wave_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_governance_wave_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_governance_wave_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_governance_wave_side_effects[2] = {
  "spawn_processes",
  "write_files",
};
static const char* cmd_yai_governance_wave_law_hooks[2] = {
  "I-002",
  "I-001",
};
static const char* cmd_yai_governance_wave_law_invariants[2] = {
  "I-002-determinism",
  "I-001-traceability",
};
static const char* cmd_yai_governance_wave_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_governance_wave_uses_primitives[3] = {
  "T-013",
  "T-012",
  "S-015",
};
static const yai_law_command_t cmd_yai_governance_wave = {
  .id = "yai.governance.wave",
  .name = "wave",
  .group = "governance",
  .summary = "Wave ops (plan/execute/select/summarize)",
  .args = cmd_yai_governance_wave_args,
  .args_len = 1,
  .outputs = cmd_yai_governance_wave_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_governance_wave_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_governance_wave_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_governance_wave_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_governance_wave_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_governance_wave_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_bundle_bundle_arg0_values[6] = {
  "build",
  "seal",
  "export",
  "import",
  "verify",
  "show",
};
static const yai_law_arg_t cmd_yai_bundle_bundle_args[2] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_bundle_bundle_arg0_values,
    .values_len = 6,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
  {
    .name = "path",
    .flag = NULL,
    .pos = 2,
    .type = "string",
    .values = NULL,
    .values_len = 0,
    .required = 0,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_bundle_bundle_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_bundle_bundle_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_bundle_bundle_law_hooks[3] = {
  "I-001",
  "I-002",
  "I-003",
};
static const char* cmd_yai_bundle_bundle_law_invariants[3] = {
  "I-001-traceability",
  "I-002-determinism",
  "I-003-governance",
};
static const char* cmd_yai_bundle_bundle_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_bundle_bundle_uses_primitives[6] = {
  "T-014",
  "S-014",
  "S-013",
  "S-006",
  "S-004",
  "O-006",
};
static const yai_law_artifact_io_t cmd_yai_bundle_bundle_emits_artifacts[1] = {
  {
    .role = "bundle_manifest",
    .schema_ref = "schema/bundle_manifest.v1.schema.json",
    .path_hint = "bundle_manifest.json",
  },
};
static const yai_law_artifact_io_t cmd_yai_bundle_bundle_consumes_artifacts[1] = {
  {
    .role = "evidence_index",
    .schema_ref = "schema/evidence_index.v1.schema.json",
    .path_hint = "evidence_index.json",
  },
};
static const yai_law_command_t cmd_yai_bundle_bundle = {
  .id = "yai.bundle.bundle",
  .name = "bundle",
  .group = "bundle",
  .summary = "Bundle ops (build/seal/export/import/verify/show)",
  .args = cmd_yai_bundle_bundle_args,
  .args_len = 2,
  .outputs = cmd_yai_bundle_bundle_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_bundle_bundle_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_bundle_bundle_law_hooks,
  .law_hooks_len = 3,
  .law_invariants = cmd_yai_bundle_bundle_law_invariants,
  .law_invariants_len = 3,
  .law_boundaries = cmd_yai_bundle_bundle_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_bundle_bundle_uses_primitives,
  .uses_primitives_len = 6,
  .emits_artifacts = cmd_yai_bundle_bundle_emits_artifacts,
  .emits_artifacts_len = 1,
  .consumes_artifacts = cmd_yai_bundle_bundle_consumes_artifacts,
  .consumes_artifacts_len = 1,
};

static const char* cmd_yai_governance_claim_arg0_values[4] = {
  "declare",
  "scope",
  "link-evidence",
  "verify",
};
static const yai_law_arg_t cmd_yai_governance_claim_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_governance_claim_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_governance_claim_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_governance_claim_side_effects[1] = {
  "write_files",
};
static const char* cmd_yai_governance_claim_law_hooks[2] = {
  "I-001",
  "I-003",
};
static const char* cmd_yai_governance_claim_law_invariants[2] = {
  "I-001-traceability",
  "I-003-governance",
};
static const char* cmd_yai_governance_claim_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_governance_claim_uses_primitives[3] = {
  "T-016",
  "T-021",
  "T-011",
};
static const yai_law_command_t cmd_yai_governance_claim = {
  .id = "yai.governance.claim",
  .name = "claim",
  .group = "governance",
  .summary = "Claim ops (declare/scope/link-evidence/verify)",
  .args = cmd_yai_governance_claim_args,
  .args_len = 1,
  .outputs = cmd_yai_governance_claim_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_governance_claim_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_governance_claim_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_governance_claim_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_governance_claim_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_governance_claim_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_governance_assert_arg0_values[3] = {
  "evaluate",
  "record",
  "aggregate",
};
static const yai_law_arg_t cmd_yai_governance_assert_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_governance_assert_arg0_values,
    .values_len = 3,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_governance_assert_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_governance_assert_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_governance_assert_law_hooks[2] = {
  "I-001",
  "I-002",
};
static const char* cmd_yai_governance_assert_law_invariants[2] = {
  "I-001-traceability",
  "I-002-determinism",
};
static const char* cmd_yai_governance_assert_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_governance_assert_uses_primitives[3] = {
  "T-017",
  "S-011",
  "S-012",
};
static const yai_law_command_t cmd_yai_governance_assert = {
  .id = "yai.governance.assert",
  .name = "assert",
  .group = "governance",
  .summary = "Assertion ops (evaluate/record/aggregate)",
  .args = cmd_yai_governance_assert_args,
  .args_len = 1,
  .outputs = cmd_yai_governance_assert_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_governance_assert_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_governance_assert_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_governance_assert_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_governance_assert_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_governance_assert_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_governance_controls_arg0_values[3] = {
  "define",
  "map",
  "audit",
};
static const yai_law_arg_t cmd_yai_governance_controls_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_governance_controls_arg0_values,
    .values_len = 3,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_governance_controls_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_governance_controls_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_governance_controls_law_hooks[1] = {
  "I-003",
};
static const char* cmd_yai_governance_controls_law_invariants[1] = {
  "I-003-governance",
};
static const char* cmd_yai_governance_controls_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_governance_controls_uses_primitives[3] = {
  "T-018",
  "T-004",
  "T-019",
};
static const yai_law_command_t cmd_yai_governance_controls = {
  .id = "yai.governance.controls",
  .name = "controls",
  .group = "governance",
  .summary = "Controls catalog ops (define/map/audit)",
  .args = cmd_yai_governance_controls_args,
  .args_len = 1,
  .outputs = cmd_yai_governance_controls_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_governance_controls_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_governance_controls_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_governance_controls_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_governance_controls_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_governance_controls_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_governance_invariant_arg0_values[3] = {
  "list",
  "check",
  "explain",
};
static const yai_law_arg_t cmd_yai_governance_invariant_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_governance_invariant_arg0_values,
    .values_len = 3,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_governance_invariant_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_governance_invariant_side_effects[1] = {
  "read_files",
};
static const char* cmd_yai_governance_invariant_law_hooks[2] = {
  "I-003",
  "I-001",
};
static const char* cmd_yai_governance_invariant_law_invariants[2] = {
  "I-003-governance",
  "I-001-traceability",
};
static const char* cmd_yai_governance_invariant_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_governance_invariant_uses_primitives[3] = {
  "T-019",
  "S-011",
  "S-008",
};
static const yai_law_command_t cmd_yai_governance_invariant = {
  .id = "yai.governance.invariant",
  .name = "invariant",
  .group = "governance",
  .summary = "Invariant ops (list/check/explain)",
  .args = cmd_yai_governance_invariant_args,
  .args_len = 1,
  .outputs = cmd_yai_governance_invariant_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_governance_invariant_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_governance_invariant_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_governance_invariant_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_governance_invariant_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_governance_invariant_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_governance_exception_arg0_values[4] = {
  "grant",
  "scope",
  "expire",
  "audit",
};
static const yai_law_arg_t cmd_yai_governance_exception_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_governance_exception_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_governance_exception_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_governance_exception_side_effects[1] = {
  "write_files",
};
static const char* cmd_yai_governance_exception_law_hooks[1] = {
  "I-003",
};
static const char* cmd_yai_governance_exception_law_invariants[1] = {
  "I-003-governance",
};
static const char* cmd_yai_governance_exception_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_governance_exception_uses_primitives[2] = {
  "T-020",
  "T-021",
};
static const yai_law_command_t cmd_yai_governance_exception = {
  .id = "yai.governance.exception",
  .name = "exception",
  .group = "governance",
  .summary = "Exception ops (grant/scope/expire/audit)",
  .args = cmd_yai_governance_exception_args,
  .args_len = 1,
  .outputs = cmd_yai_governance_exception_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_governance_exception_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_governance_exception_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_governance_exception_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_governance_exception_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_governance_exception_uses_primitives,
  .uses_primitives_len = 2,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_governance_scope_arg0_values[3] = {
  "define",
  "match",
  "serialize",
};
static const yai_law_arg_t cmd_yai_governance_scope_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_governance_scope_arg0_values,
    .values_len = 3,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_governance_scope_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_governance_scope_side_effects[1] = {
  "write_files",
};
static const char* cmd_yai_governance_scope_law_hooks[1] = {
  "I-003",
};
static const char* cmd_yai_governance_scope_law_invariants[1] = {
  "I-003-governance",
};
static const char* cmd_yai_governance_scope_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_governance_scope_uses_primitives[3] = {
  "T-021",
  "S-001",
  "S-002",
};
static const yai_law_command_t cmd_yai_governance_scope = {
  .id = "yai.governance.scope",
  .name = "scope",
  .group = "governance",
  .summary = "Scope ops (define/match/serialize)",
  .args = cmd_yai_governance_scope_args,
  .args_len = 1,
  .outputs = cmd_yai_governance_scope_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_governance_scope_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_governance_scope_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_governance_scope_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_governance_scope_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_governance_scope_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_governance_disclosure_arg0_values[3] = {
  "declare",
  "prove-nonleak",
  "verify",
};
static const yai_law_arg_t cmd_yai_governance_disclosure_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_governance_disclosure_arg0_values,
    .values_len = 3,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_governance_disclosure_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_governance_disclosure_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_governance_disclosure_law_hooks[2] = {
  "I-001",
  "I-003",
};
static const char* cmd_yai_governance_disclosure_law_invariants[2] = {
  "I-001-traceability",
  "I-003-governance",
};
static const char* cmd_yai_governance_disclosure_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_governance_disclosure_uses_primitives[2] = {
  "T-023",
  "T-011",
};
static const yai_law_command_t cmd_yai_governance_disclosure = {
  .id = "yai.governance.disclosure",
  .name = "disclosure",
  .group = "governance",
  .summary = "Disclosure ops (declare/prove-nonleak/verify)",
  .args = cmd_yai_governance_disclosure_args,
  .args_len = 1,
  .outputs = cmd_yai_governance_disclosure_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_governance_disclosure_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_governance_disclosure_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_governance_disclosure_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_governance_disclosure_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_governance_disclosure_uses_primitives,
  .uses_primitives_len = 2,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_orch_pack_arg0_values[4] = {
  "install",
  "pin",
  "list",
  "resolve",
};
static const yai_law_arg_t cmd_yai_orch_pack_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_orch_pack_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_orch_pack_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_orch_pack_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_orch_pack_law_hooks[2] = {
  "I-002",
  "I-003",
};
static const char* cmd_yai_orch_pack_law_invariants[2] = {
  "I-002-determinism",
  "I-003-governance",
};
static const char* cmd_yai_orch_pack_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_orch_pack_uses_primitives[5] = {
  "O-001",
  "S-006",
  "S-018",
  "T-004",
  "T-006",
};
static const yai_law_command_t cmd_yai_orch_pack = {
  .id = "yai.orch.pack",
  .name = "pack",
  .group = "orch",
  .summary = "Pack ops (install/pin/list/resolve)",
  .args = cmd_yai_orch_pack_args,
  .args_len = 1,
  .outputs = cmd_yai_orch_pack_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_orch_pack_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_orch_pack_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_orch_pack_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_orch_pack_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_orch_pack_uses_primitives,
  .uses_primitives_len = 5,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_orch_trial_arg0_values[4] = {
  "run",
  "describe",
  "list",
  "replay",
};
static const yai_law_arg_t cmd_yai_orch_trial_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_orch_trial_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_orch_trial_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_orch_trial_side_effects[1] = {
  "spawn_processes",
};
static const char* cmd_yai_orch_trial_law_hooks[2] = {
  "I-001",
  "I-002",
};
static const char* cmd_yai_orch_trial_law_invariants[2] = {
  "I-001-traceability",
  "I-002-determinism",
};
static const char* cmd_yai_orch_trial_law_boundaries[3] = {
  "L1-kernel",
  "L2-engine",
  "L3-mind",
};
static const char* cmd_yai_orch_trial_uses_primitives[4] = {
  "O-002",
  "T-012",
  "S-029",
  "S-034",
};
static const yai_law_command_t cmd_yai_orch_trial = {
  .id = "yai.orch.trial",
  .name = "trial",
  .group = "orch",
  .summary = "Trial ops (run/describe/list/replay)",
  .args = cmd_yai_orch_trial_args,
  .args_len = 1,
  .outputs = cmd_yai_orch_trial_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_orch_trial_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_orch_trial_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_orch_trial_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_orch_trial_law_boundaries,
  .law_boundaries_len = 3,
  .uses_primitives = cmd_yai_orch_trial_uses_primitives,
  .uses_primitives_len = 4,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_orch_plan_arg0_values[4] = {
  "render",
  "lock",
  "execute",
  "diff",
};
static const yai_law_arg_t cmd_yai_orch_plan_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_orch_plan_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_orch_plan_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_orch_plan_side_effects[3] = {
  "read_files",
  "write_files",
  "spawn_processes",
};
static const char* cmd_yai_orch_plan_law_hooks[1] = {
  "I-002",
};
static const char* cmd_yai_orch_plan_law_invariants[1] = {
  "I-002-determinism",
};
static const char* cmd_yai_orch_plan_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_orch_plan_uses_primitives[3] = {
  "O-003",
  "S-015",
  "S-034",
};
static const yai_law_command_t cmd_yai_orch_plan = {
  .id = "yai.orch.plan",
  .name = "plan",
  .group = "orch",
  .summary = "Plan ops (render/lock/execute/diff)",
  .args = cmd_yai_orch_plan_args,
  .args_len = 1,
  .outputs = cmd_yai_orch_plan_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_orch_plan_side_effects,
  .side_effects_len = 3,
  .law_hooks = cmd_yai_orch_plan_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_orch_plan_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_orch_plan_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_orch_plan_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_orch_runner_arg0_values[4] = {
  "execute",
  "emit",
  "checkpoint",
  "abort",
};
static const yai_law_arg_t cmd_yai_orch_runner_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_orch_runner_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_orch_runner_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_orch_runner_side_effects[2] = {
  "spawn_processes",
  "write_files",
};
static const char* cmd_yai_orch_runner_law_hooks[2] = {
  "I-001",
  "I-002",
};
static const char* cmd_yai_orch_runner_law_invariants[2] = {
  "I-001-traceability",
  "I-002-determinism",
};
static const char* cmd_yai_orch_runner_law_boundaries[2] = {
  "L1-kernel",
  "L2-engine",
};
static const char* cmd_yai_orch_runner_uses_primitives[4] = {
  "O-004",
  "S-042",
  "S-008",
  "O-005",
};
static const yai_law_command_t cmd_yai_orch_runner = {
  .id = "yai.orch.runner",
  .name = "runner",
  .group = "orch",
  .summary = "Runner ops (execute/emit/checkpoint/abort)",
  .args = cmd_yai_orch_runner_args,
  .args_len = 1,
  .outputs = cmd_yai_orch_runner_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_orch_runner_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_orch_runner_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_orch_runner_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_orch_runner_law_boundaries,
  .law_boundaries_len = 2,
  .uses_primitives = cmd_yai_orch_runner_uses_primitives,
  .uses_primitives_len = 4,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_orch_emit_arg0_values[5] = {
  "emit-event",
  "emit-decision",
  "emit-effect",
  "emit-metrics",
  "flush",
};
static const yai_law_arg_t cmd_yai_orch_emit_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_orch_emit_arg0_values,
    .values_len = 5,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_orch_emit_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_orch_emit_side_effects[1] = {
  "write_files",
};
static const char* cmd_yai_orch_emit_law_hooks[1] = {
  "I-001",
};
static const char* cmd_yai_orch_emit_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_orch_emit_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_orch_emit_uses_primitives[5] = {
  "O-005",
  "S-010",
  "S-004",
  "S-005",
  "S-013",
};
static const yai_law_command_t cmd_yai_orch_emit = {
  .id = "yai.orch.emit",
  .name = "emit",
  .group = "orch",
  .summary = "Emitter ops (emit-event/emit-decision/emit-effect/emit-metrics/flush)",
  .args = cmd_yai_orch_emit_args,
  .args_len = 1,
  .outputs = cmd_yai_orch_emit_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_orch_emit_side_effects,
  .side_effects_len = 1,
  .law_hooks = cmd_yai_orch_emit_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_orch_emit_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_orch_emit_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_orch_emit_uses_primitives,
  .uses_primitives_len = 5,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_orch_job_arg0_values[4] = {
  "schedule",
  "run",
  "status",
  "cancel",
};
static const yai_law_arg_t cmd_yai_orch_job_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_orch_job_arg0_values,
    .values_len = 4,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_orch_job_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_orch_job_side_effects[2] = {
  "spawn_processes",
  "write_files",
};
static const char* cmd_yai_orch_job_law_hooks[1] = {
  "I-001",
};
static const char* cmd_yai_orch_job_law_invariants[1] = {
  "I-001-traceability",
};
static const char* cmd_yai_orch_job_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_orch_job_uses_primitives[3] = {
  "O-009",
  "S-026",
  "S-016",
};
static const yai_law_command_t cmd_yai_orch_job = {
  .id = "yai.orch.job",
  .name = "job",
  .group = "orch",
  .summary = "Job ops (schedule/run/status/cancel)",
  .args = cmd_yai_orch_job_args,
  .args_len = 1,
  .outputs = cmd_yai_orch_job_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_orch_job_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_orch_job_law_hooks,
  .law_hooks_len = 1,
  .law_invariants = cmd_yai_orch_job_law_invariants,
  .law_invariants_len = 1,
  .law_boundaries = cmd_yai_orch_job_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_orch_job_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const char* cmd_yai_orch_report_arg0_values[3] = {
  "build",
  "render",
  "export",
};
static const yai_law_arg_t cmd_yai_orch_report_args[1] = {
  {
    .name = "op",
    .flag = NULL,
    .pos = 1,
    .type = "enum",
    .values = cmd_yai_orch_report_arg0_values,
    .values_len = 3,
    .required = 1,
    .default_s = NULL,
    .default_b_set = 0,
    .default_b = 0,
    .default_i_set = 0,
    .default_i = 0,
  },
};

static const char* cmd_yai_orch_report_outputs[2] = {
  "text",
  "json",
};
static const char* cmd_yai_orch_report_side_effects[2] = {
  "read_files",
  "write_files",
};
static const char* cmd_yai_orch_report_law_hooks[2] = {
  "I-001",
  "I-003",
};
static const char* cmd_yai_orch_report_law_invariants[2] = {
  "I-001-traceability",
  "I-003-governance",
};
static const char* cmd_yai_orch_report_law_boundaries[1] = {
  "Lx-docs",
};
static const char* cmd_yai_orch_report_uses_primitives[3] = {
  "O-010",
  "S-013",
  "T-022",
};
static const yai_law_command_t cmd_yai_orch_report = {
  .id = "yai.orch.report",
  .name = "report",
  .group = "orch",
  .summary = "Report ops (build/render/export)",
  .args = cmd_yai_orch_report_args,
  .args_len = 1,
  .outputs = cmd_yai_orch_report_outputs,
  .outputs_len = 2,
  .side_effects = cmd_yai_orch_report_side_effects,
  .side_effects_len = 2,
  .law_hooks = cmd_yai_orch_report_law_hooks,
  .law_hooks_len = 2,
  .law_invariants = cmd_yai_orch_report_law_invariants,
  .law_invariants_len = 2,
  .law_boundaries = cmd_yai_orch_report_law_boundaries,
  .law_boundaries_len = 1,
  .uses_primitives = cmd_yai_orch_report_uses_primitives,
  .uses_primitives_len = 3,
  .emits_artifacts = NULL,
  .emits_artifacts_len = 0,
  .consumes_artifacts = NULL,
  .consumes_artifacts_len = 0,
};

static const yai_law_command_t g_commands[80] = {
  cmd_yai_lifecycle_up,
  cmd_yai_lifecycle_restart,
  cmd_yai_lifecycle_down,
  cmd_yai_inspect_status,
  cmd_yai_inspect_logs,
  cmd_yai_inspect_monitor,
  cmd_yai_inspect_events,
  cmd_yai_verify_verify,
  cmd_yai_verify_test,
  cmd_yai_control_providers,
  cmd_yai_control_dsar,
  cmd_yai_control_sessions,
  cmd_yai_control_chat,
  cmd_yai_control_shell,
  cmd_yai_control_root,
  cmd_yai_control_kernel,
  cmd_yai_memory_graph,
  cmd_yai_memory_embed,
  cmd_yai_substrate_ns,
  cmd_yai_substrate_ref,
  cmd_yai_substrate_key,
  cmd_yai_substrate_hash,
  cmd_yai_substrate_artifact,
  cmd_yai_substrate_store,
  cmd_yai_substrate_schema,
  cmd_yai_substrate_validate,
  cmd_yai_substrate_clock,
  cmd_yai_substrate_record,
  cmd_yai_substrate_timeline,
  cmd_yai_substrate_metrics,
  cmd_yai_substrate_index,
  cmd_yai_substrate_manifest,
  cmd_yai_substrate_select,
  cmd_yai_substrate_channel,
  cmd_yai_substrate_env,
  cmd_yai_substrate_compat,
  cmd_yai_substrate_fs,
  cmd_yai_substrate_stream,
  cmd_yai_substrate_lock,
  cmd_yai_substrate_txn,
  cmd_yai_substrate_error,
  cmd_yai_substrate_resource,
  cmd_yai_substrate_quota,
  cmd_yai_substrate_sandbox,
  cmd_yai_substrate_cap,
  cmd_yai_substrate_net,
  cmd_yai_substrate_codec,
  cmd_yai_substrate_seed,
  cmd_yai_substrate_prov,
  cmd_yai_substrate_journal,
  cmd_yai_substrate_checkpoint,
  cmd_yai_substrate_diff,
  cmd_yai_substrate_patch,
  cmd_yai_governance_event,
  cmd_yai_governance_identity,
  cmd_yai_governance_authority,
  cmd_yai_governance_contract,
  cmd_yai_governance_baseline,
  cmd_yai_governance_policy,
  cmd_yai_governance_decision,
  cmd_yai_governance_reason,
  cmd_yai_governance_effect,
  cmd_yai_governance_evidence,
  cmd_yai_governance_run,
  cmd_yai_governance_wave,
  cmd_yai_bundle_bundle,
  cmd_yai_governance_claim,
  cmd_yai_governance_assert,
  cmd_yai_governance_controls,
  cmd_yai_governance_invariant,
  cmd_yai_governance_exception,
  cmd_yai_governance_scope,
  cmd_yai_governance_disclosure,
  cmd_yai_orch_pack,
  cmd_yai_orch_trial,
  cmd_yai_orch_plan,
  cmd_yai_orch_runner,
  cmd_yai_orch_emit,
  cmd_yai_orch_job,
  cmd_yai_orch_report,
};

static const yai_law_registry_t g_registry = {
  .version = "1.0",
  .binary = "yai",
  .commands = g_commands,
  .commands_len = 80,
  .artifacts = g_artifacts,
  .artifacts_len = 6,
};

const yai_law_registry_t* yai_law_registry_cache(void) {
  return &g_registry;
}

const yai_law_command_t* yai_law_registry_find_command(const char* id) {
  if (!id) return NULL;
  for (size_t i = 0; i < g_registry.commands_len; i++) {
    const yai_law_command_t* c = &g_registry.commands[i];
    if (c->id && strcmp(c->id, id) == 0) return c;
  }
  return NULL;
}

const yai_law_artifact_role_t* yai_law_registry_find_artifact_role(const char* role) {
  if (!role) return NULL;
  for (size_t i = 0; i < g_registry.artifacts_len; i++) {
    const yai_law_artifact_role_t* a = &g_registry.artifacts[i];
    if (a->role && strcmp(a->role, role) == 0) return a;
  }
  return NULL;
}

int yai_law_registry_cache_validate(void) {
  for (size_t i = 0; i < g_registry.commands_len; i++) {
    const yai_law_command_t* a = &g_registry.commands[i];
    if (!a->id || !a->name || !a->group || !a->summary) return 1;
    for (size_t j = i + 1; j < g_registry.commands_len; j++) {
      const yai_law_command_t* b = &g_registry.commands[j];
      if (b->id && strcmp(a->id, b->id) == 0) return 2;
    }
  }
  for (size_t i = 0; i < g_registry.artifacts_len; i++) {
    const yai_law_artifact_role_t* a = &g_registry.artifacts[i];
    if (!a->role || !a->schema_ref || !a->description) return 3;
  }
  return 0;
}
