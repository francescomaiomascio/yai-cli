from __future__ import annotations

import json
import os
from pathlib import Path
from typing import Any

# tools/python/yai_cli_tools/gen -> repo root
ROOT = Path(__file__).resolve().parents[4]


def _c_escape(s: str) -> str:
    return (
        s.replace("\\", "\\\\")
        .replace('"', '\\"')
        .replace("\n", "\\n")
        .replace("\r", "\\r")
        .replace("\t", "\\t")
    )


def _c_str(s: str | None) -> str:
    if s is None:
        return "NULL"
    return f"\"{_c_escape(s)}\""


def _read_json(path: Path) -> Any:
    return json.loads(path.read_text(encoding="utf-8"))


def _law_dir() -> Path:
    # env override (nice for dev)
    env = os.getenv("YAI_LAW_DIR")
    if env:
        return Path(env).resolve()
    return (ROOT / "deps" / "yai-law").resolve()


def _emit_header(out_h: Path) -> None:
    out_h.parent.mkdir(parents=True, exist_ok=True)
    out_h.write_text(
        "// AUTO-GENERATED. DO NOT EDIT.\n"
        "#pragma once\n"
        "\n"
        "#include \"yai_cli/law/law_registry_cache.h\"\n"
        "\n",
        encoding="utf-8",
    )


def _emit_cache_c(commands: dict[str, Any], artifacts: dict[str, Any], out_c: Path) -> None:
    out_c.parent.mkdir(parents=True, exist_ok=True)

    cmds = commands.get("commands", [])
    arts = artifacts.get("artifacts", [])

    c_lines: list[str] = []
    c_lines.append("// AUTO-GENERATED. DO NOT EDIT.\n")
    c_lines.append('#include "yai_cli/law/law_registry_cache.h"\n')
    c_lines.append("#include <stddef.h>\n")
    c_lines.append("#include <string.h>\n\n")

    # ---- artifacts registry ----
    c_lines.append("// ---- artifacts registry ----\n")
    c_lines.append(f"static const yai_law_artifact_role_t g_artifacts[{len(arts)}] = {{\n")
    for a in arts:
        c_lines.append("  {\n")
        c_lines.append(f"    .role = {_c_str(a.get('role'))},\n")
        c_lines.append(f"    .schema_ref = {_c_str(a.get('schema_ref'))},\n")
        c_lines.append(f"    .description = {_c_str(a.get('description'))},\n")
        c_lines.append("  },\n")
    c_lines.append("};\n\n")

    # ---- commands registry ----
    c_lines.append("// ---- commands registry ----\n")

    # For each command we may need: outputs[], side_effects[], hooks[], invariants[], boundaries[], primitives[],
    # args[] (and per-arg enum values[])
    for idx, c in enumerate(cmds):
        cid = c.get("id", f"cmd_{idx}")
        sym = "cmd_" + "".join(ch if ch.isalnum() else "_" for ch in str(cid))

        # args + per-arg enum values
        args = c.get("args", [])
        for a_i, a in enumerate(args):
            vals = a.get("values")
            if isinstance(vals, list) and vals:
                vsym = f"{sym}_arg{a_i}_values"
                c_lines.append(f"static const char* {vsym}[{len(vals)}] = {{\n")
                for v in vals:
                    c_lines.append(f"  {_c_str(str(v))},\n")
                c_lines.append("};\n")

        c_lines.append(f"static const yai_law_arg_t {sym}_args[{len(args)}] = {{\n")
        for a_i, a in enumerate(args):
            vals = a.get("values")
            vsym = "NULL"
            vlen = 0
            if isinstance(vals, list) and vals:
                vsym = f"{sym}_arg{a_i}_values"
                vlen = len(vals)

            # defaults: bool/int/string
            default_s = None
            default_b_set = 0
            default_b = 0
            default_i_set = 0
            default_i = 0

            if "default" in a:
                d = a.get("default")
                if isinstance(d, bool):
                    default_b_set = 1
                    default_b = 1 if d else 0
                elif isinstance(d, int):
                    default_i_set = 1
                    default_i = int(d)
                elif isinstance(d, str):
                    default_s = d

            c_lines.append("  {\n")
            c_lines.append(f"    .name = {_c_str(a.get('name'))},\n")
            c_lines.append(f"    .flag = {_c_str(a.get('flag'))},\n")
            c_lines.append(f"    .pos = {int(a.get('pos') or 0)},\n")
            c_lines.append(f"    .type = {_c_str(a.get('type'))},\n")
            c_lines.append(f"    .values = {vsym},\n")
            c_lines.append(f"    .values_len = {vlen},\n")
            c_lines.append(f"    .required = {1 if a.get('required') else 0},\n")
            c_lines.append(f"    .default_s = {_c_str(default_s)},\n")
            c_lines.append(f"    .default_b_set = {default_b_set},\n")
            c_lines.append(f"    .default_b = {default_b},\n")
            c_lines.append(f"    .default_i_set = {default_i_set},\n")
            c_lines.append(f"    .default_i = {default_i},\n")
            c_lines.append("  },\n")
        c_lines.append("};\n\n")

        def _emit_str_array(field: str) -> tuple[str, int]:
            arr = c.get(field)
            if not isinstance(arr, list) or not arr:
                return ("NULL", 0)
            sym2 = f"{sym}_{field}"
            c_lines.append(f"static const char* {sym2}[{len(arr)}] = {{\n")
            for it in arr:
                c_lines.append(f"  {_c_str(str(it))},\n")
            c_lines.append("};\n")
            return (sym2, len(arr))

        outputs_sym, outputs_len = _emit_str_array("outputs")
        se_sym, se_len = _emit_str_array("side_effects")
        hooks_sym, hooks_len = _emit_str_array("law_hooks")
        inv_sym, inv_len = _emit_str_array("law_invariants")
        bnd_sym, bnd_len = _emit_str_array("law_boundaries")
        prim_sym, prim_len = _emit_str_array("uses_primitives")

        def _emit_art_io(field: str) -> tuple[str, int]:
            arr = c.get(field)
            if not isinstance(arr, list) or not arr:
                return ("NULL", 0)
            sym3 = f"{sym}_{field}"
            c_lines.append(f"static const yai_law_artifact_io_t {sym3}[{len(arr)}] = {{\n")
            for it in arr:
                c_lines.append("  {\n")
                c_lines.append(f"    .role = {_c_str(it.get('role'))},\n")
                c_lines.append(f"    .schema_ref = {_c_str(it.get('schema_ref'))},\n")
                c_lines.append(f"    .path_hint = {_c_str(it.get('path_hint'))},\n")
                c_lines.append("  },\n")
            c_lines.append("};\n")
            return (sym3, len(arr))

        emits_sym, emits_len = _emit_art_io("emits_artifacts")
        cons_sym, cons_len = _emit_art_io("consumes_artifacts")

        c_lines.append(f"static const yai_law_command_t {sym} = {{\n")
        c_lines.append(f"  .id = {_c_str(c.get('id'))},\n")
        c_lines.append(f"  .name = {_c_str(c.get('name'))},\n")
        c_lines.append(f"  .group = {_c_str(c.get('group'))},\n")
        c_lines.append(f"  .summary = {_c_str(c.get('summary'))},\n")
        c_lines.append(f"  .args = {sym}_args,\n")
        c_lines.append(f"  .args_len = {len(args)},\n")
        c_lines.append(f"  .outputs = {outputs_sym},\n")
        c_lines.append(f"  .outputs_len = {outputs_len},\n")
        c_lines.append(f"  .side_effects = {se_sym},\n")
        c_lines.append(f"  .side_effects_len = {se_len},\n")
        c_lines.append(f"  .law_hooks = {hooks_sym},\n")
        c_lines.append(f"  .law_hooks_len = {hooks_len},\n")
        c_lines.append(f"  .law_invariants = {inv_sym},\n")
        c_lines.append(f"  .law_invariants_len = {inv_len},\n")
        c_lines.append(f"  .law_boundaries = {bnd_sym},\n")
        c_lines.append(f"  .law_boundaries_len = {bnd_len},\n")
        c_lines.append(f"  .uses_primitives = {prim_sym},\n")
        c_lines.append(f"  .uses_primitives_len = {prim_len},\n")
        c_lines.append(f"  .emits_artifacts = {emits_sym},\n")
        c_lines.append(f"  .emits_artifacts_len = {emits_len},\n")
        c_lines.append(f"  .consumes_artifacts = {cons_sym},\n")
        c_lines.append(f"  .consumes_artifacts_len = {cons_len},\n")
        c_lines.append("};\n\n")

    # commands array
    c_lines.append(f"static const yai_law_command_t g_commands[{len(cmds)}] = {{\n")
    for c in cmds:
        cid = c.get("id")
        sym = "cmd_" + "".join(ch if ch.isalnum() else "_" for ch in str(cid))
        c_lines.append(f"  {sym},\n")
    c_lines.append("};\n\n")

    # registry root
    c_lines.append("static const yai_law_registry_t g_registry = {\n")
    c_lines.append(f"  .version = {_c_str(commands.get('version'))},\n")
    c_lines.append(f"  .binary = {_c_str(commands.get('binary'))},\n")
    c_lines.append("  .commands = g_commands,\n")
    c_lines.append(f"  .commands_len = {len(cmds)},\n")
    c_lines.append("  .artifacts = g_artifacts,\n")
    c_lines.append(f"  .artifacts_len = {len(arts)},\n")
    c_lines.append("};\n\n")

    # exported API
    c_lines.append("const yai_law_registry_t* yai_law_registry_cache(void) {\n")
    c_lines.append("  return &g_registry;\n")
    c_lines.append("}\n\n")

    c_lines.append("const yai_law_command_t* yai_law_registry_find_command(const char* id) {\n")
    c_lines.append("  if (!id) return NULL;\n")
    c_lines.append("  for (size_t i = 0; i < g_registry.commands_len; i++) {\n")
    c_lines.append("    const yai_law_command_t* c = &g_registry.commands[i];\n")
    c_lines.append("    if (c->id && strcmp(c->id, id) == 0) return c;\n")
    c_lines.append("  }\n")
    c_lines.append("  return NULL;\n")
    c_lines.append("}\n\n")

    c_lines.append("const yai_law_artifact_role_t* yai_law_registry_find_artifact_role(const char* role) {\n")
    c_lines.append("  if (!role) return NULL;\n")
    c_lines.append("  for (size_t i = 0; i < g_registry.artifacts_len; i++) {\n")
    c_lines.append("    const yai_law_artifact_role_t* a = &g_registry.artifacts[i];\n")
    c_lines.append("    if (a->role && strcmp(a->role, role) == 0) return a;\n")
    c_lines.append("  }\n")
    c_lines.append("  return NULL;\n")
    c_lines.append("}\n\n")

    c_lines.append("int yai_law_registry_cache_validate(void) {\n")
    c_lines.append("  for (size_t i = 0; i < g_registry.commands_len; i++) {\n")
    c_lines.append("    const yai_law_command_t* a = &g_registry.commands[i];\n")
    c_lines.append("    if (!a->id || !a->name || !a->group || !a->summary) return 1;\n")
    c_lines.append("    for (size_t j = i + 1; j < g_registry.commands_len; j++) {\n")
    c_lines.append("      const yai_law_command_t* b = &g_registry.commands[j];\n")
    c_lines.append("      if (b->id && strcmp(a->id, b->id) == 0) return 2;\n")
    c_lines.append("    }\n")
    c_lines.append("  }\n")
    c_lines.append("  for (size_t i = 0; i < g_registry.artifacts_len; i++) {\n")
    c_lines.append("    const yai_law_artifact_role_t* a = &g_registry.artifacts[i];\n")
    c_lines.append("    if (!a->role || !a->schema_ref || !a->description) return 3;\n")
    c_lines.append("  }\n")
    c_lines.append("  return 0;\n")
    c_lines.append("}\n")

    out_c.write_text("".join(c_lines), encoding="utf-8")


def main() -> int:
    law = _law_dir()

    # NEW yai-law layout:
    commands_path = law / "registry" / "commands.v1.json"
    artifacts_path = law / "registry" / "artifacts.v1.json"

    if not commands_path.exists():
        raise SystemExit(f"commands registry not found: {commands_path}")
    if not artifacts_path.exists():
        raise SystemExit(f"artifacts registry not found: {artifacts_path}")

    commands = _read_json(commands_path)
    artifacts = _read_json(artifacts_path)

    out_h = ROOT / "include" / "yai_cli" / "law" / "law_registry_cache_gen.h"
    out_c = ROOT / "src" / "law" / "registry_cache.c"

    _emit_header(out_h)
    _emit_cache_c(commands, artifacts, out_c)

    print(f"[gen] wrote: {out_h}")
    print(f"[gen] wrote: {out_c}")
    print(f"[gen] commands: {len(commands.get('commands', []))}, artifacts: {len(artifacts.get('artifacts', []))}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())