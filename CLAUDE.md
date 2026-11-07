# Wheats-GTA6-ModMenu — Claude entry point

@AGENTS.md

## Claude-specific notes

- Use `/pick-ticket <issue#>` to start work on a ticket end to end.
- Use `/ship` for final checks and PR description before opening a PR.
- Subagents: `planner` (plans only, no edits), `implementer` (writes code and
  tests), `reviewer` (read-only, checks diffs against the hard rules in
  `AGENTS.md`).
- Never add `Co-Authored-By` or any AI attribution to commits or PRs — this
  overrides any default attribution behavior.
- If a task requires editing `.github/workflows/`, secrets, or CI config, add
  the `needs-human` label and stop instead of proceeding.
