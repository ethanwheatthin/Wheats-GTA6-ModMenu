#!/usr/bin/env python3
"""Reject commit messages that don't follow Conventional Commits."""
import re
import sys

PATTERN = re.compile(
    r"^(feat|fix|docs|style|refactor|perf|test|build|ci|chore|revert)"
    r"(\([a-z0-9/_-]+\))?!?: .{1,100}"
)


def main() -> int:
    path = sys.argv[1]
    with open(path, encoding="utf-8") as f:
        subject = f.readline().strip()

    if subject.startswith("Merge ") or subject.startswith("Revert \""):
        return 0

    if not PATTERN.match(subject):
        print(
            "Commit message does not follow Conventional Commits "
            "(e.g. 'feat: add teleport command'):\n  " + subject
        )
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
