# Setup checklist (human-only steps)

Nothing below was done automatically. No secrets were created or read by any
agent. Do these before the agent-ticket loop can run end to end.

## Repo secrets

1. **`ANTHROPIC_API_KEY`** (or **`CLAUDE_CODE_OAUTH_TOKEN`**) - repo secret,
   used by `.github/workflows/claude.yml`, `claude-review.yml`, and
   `agent-ticket.yml`.
2. **`PROJECT_TOKEN`** - a fine-grained PAT or GitHub App installation token
   with **Projects: read/write** (and `repo` read for the linked repo). The
   default `GITHUB_TOKEN` cannot edit Projects v2, so `board-sync.yml`,
   `agent-ticket.yml`, and `scripts/project-status.sh` need this secret set.

## GitHub App

3. Install the **Claude GitHub App** on this repo (required for the
   `claude.yml` / `claude-review.yml` / `agent-ticket.yml` workflows to act
   on issues/PRs as expected).

## Branch protection

4. On `main`: require a PR before merging, require 1 approval, require the
   `CI` status check to pass, require a CODEOWNERS review, disallow force
   pushes.

## Local development

5. Install the ScriptHookV SDK and an ASI loader yourself (never committed
   to this repo - see `AGENTS.md`). Set `SHV_SDK_DIR` to the SDK path
   (copy `.env.example` to `.env.local` or set it in your shell).
6. Test only on a **legitimate, legally-owned single-player install with
   online disabled**. Never load this plugin into GTA Online.

## Project board (already created by this setup, listed here for reference)

7. In the project's **Settings → Workflows** (GitHub UI), turn on the
   built-in workflows listed in `docs/workflow.md` (auto-add items, item
   closed → Done, PR merged → Done) - these aren't settable via the API/CLI
   used to create the board.
