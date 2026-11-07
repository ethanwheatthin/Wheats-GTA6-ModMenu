#!/usr/bin/env python3
"""Sync .github/labels.yml to the repo's GitHub labels. Requires `gh auth`."""
import subprocess
import sys

import yaml


def main() -> int:
    with open(".github/labels.yml", encoding="utf-8") as f:
        labels = yaml.safe_load(f)

    for label in labels:
        subprocess.run(
            [
                "gh", "label", "create", label["name"],
                "--color", label["color"],
                "--description", label.get("description", ""),
                "--force",
            ],
            check=True,
        )
    return 0


if __name__ == "__main__":
    sys.exit(main())
