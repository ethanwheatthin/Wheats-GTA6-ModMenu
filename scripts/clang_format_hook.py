#!/usr/bin/env python3
"""PostToolUse hook: clang-format any C++ file Claude just edited/wrote."""
import json
import subprocess
import sys

CPP_EXTENSIONS = (".cpp", ".hpp", ".cc", ".h")


def main() -> int:
    payload = json.load(sys.stdin)
    file_path = payload.get("tool_input", {}).get("file_path", "")
    if not file_path.endswith(CPP_EXTENSIONS):
        return 0
    subprocess.run(["clang-format", "-i", file_path], check=False)
    return 0


if __name__ == "__main__":
    sys.exit(main())
