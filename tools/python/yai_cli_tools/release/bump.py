from __future__ import annotations

from pathlib import Path

from yai_cli_tools.util import repo_root


def run() -> int:
    root = repo_root()
    version_file = root / "VERSION"
    changelog = root / "CHANGELOG.md"

    current = version_file.read_text(encoding="utf-8").strip()
    parts = current.split(".")
    if len(parts) != 3 or not all(p.isdigit() for p in parts):
        print(f"FAIL: unsupported VERSION format: {current}")
        return 1

    major, minor, patch = map(int, parts)
    new_version = f"{major}.{minor}.{patch + 1}"
    version_file.write_text(new_version + "\n", encoding="utf-8")

    if changelog.exists():
        text = changelog.read_text(encoding="utf-8")
        if "## [Unreleased]" not in text:
            text = "## [Unreleased]\n\n- TODO\n\n" + text
            changelog.write_text(text, encoding="utf-8")

    print(new_version)
    return 0
