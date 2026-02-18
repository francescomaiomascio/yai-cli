from __future__ import annotations

import argparse
import json
from pathlib import Path

from yai_cli_tools.doctor import env
from yai_cli_tools.release import bump
from yai_cli_tools.verify import build, layout, smoke, specs, tests
from yai_cli_tools.util import repo_root, print_phase


def _manifest_path(profile: str) -> Path:
    name = "verify.v1.json" if profile == "full" else "ci.v1.json"
    return repo_root() / "tools" / "manifests" / name


def _run_verify(profile: str) -> int:
    mf = _manifest_path(profile)
    data = json.loads(mf.read_text(encoding="utf-8"))
    phases = data.get("phases", [])

    mapping = {
        "layout": layout.run,
        "specs": specs.run,
        "build": build.run_phase,
        "tests": tests.run_phase,
        "smoke": smoke.run_phase,
    }

    for ph in phases:
        print_phase(ph)
        fn = mapping.get(ph)
        if fn is None:
            print(f"FAIL: unknown phase in manifest: {ph}")
            return 1
        rc = fn()
        if rc != 0:
            return rc
    return 0


def main() -> int:
    parser = argparse.ArgumentParser(prog="yai-cli-tools")
    sub = parser.add_subparsers(dest="cmd", required=True)

    p_verify = sub.add_parser("verify")
    p_verify.add_argument("--profile", choices=["ci", "full"], default="ci")

    sub.add_parser("doctor")

    p_release = sub.add_parser("release")
    p_release_sub = p_release.add_subparsers(dest="release_cmd", required=True)
    p_release_sub.add_parser("bump")

    args = parser.parse_args()

    if args.cmd == "verify":
        return _run_verify(args.profile)
    if args.cmd == "doctor":
        return env.run()
    if args.cmd == "release" and args.release_cmd == "bump":
        return bump.run()
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
