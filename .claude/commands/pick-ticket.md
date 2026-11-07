---
description: Pick up a GitHub issue end-to-end - plan, implement, test, open PR
argument-hint: <issue-number>
---

Issue number: $1

1. Run `gh issue view $1 --comments` and read the issue and every comment.
2. Restate the acceptance criteria in your own words in your response, so a
   human can catch a misunderstanding before work starts.
3. Post a short implementation plan as an issue comment:
   `gh issue comment $1 --body "<plan>"`.
4. Create a branch `agent/$1-<slug>` from the latest `main`.
5. Implement the change in small logical commits, with tests against the
   mock adapter, following `AGENTS.md` conventions (Conventional Commits,
   no AI attribution, never touch CI/secrets/workflows without `needs-human`).
6. Run `just lint`, `just typecheck`, `just test` (or the `scripts/*.ps1`
   directly) until all are green.
7. Open a PR referencing `Closes #$1`, filled out per
   `.github/pull_request_template.md`.
8. Move the card to "In Review":
   `scripts/project-status.sh <pr-number> "In Review"`.
9. If blocked or a requirement is ambiguous, comment on the issue, label it
   `needs-human` if relevant, and stop. Do not guess, do not merge.
