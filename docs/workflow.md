# Project board workflow

The board itself and its `Status` field (Backlog / Ready / In Progress /
In Review / Done) are created by `gh project`. A few GitHub Projects
built-in automations can only be toggled in the UI (no CLI/API for this as
of writing) - turn these on under the project's **... menu → Workflows**:

- **Auto-add to project**: when an issue or PR is created in this repo, add
  it to the board automatically (set Status to the default/first column).
- **Item closed → Done**: when an issue is closed, set its Status to
  `Done`.
- **Pull request merged → Done**: when a PR is merged, set its Status to
  `Done`.

These complement, rather than duplicate, the custom transitions in
`.github/workflows/board-sync.yml` and `agent-ticket.yml` (issue opened →
Backlog; PR opened referencing an issue → In Review; agent picks up a
ticket → In Progress; failure → back to Ready). If both an automation and a
workflow run set the same item's status, the more specific custom workflow
should be treated as authoritative.
