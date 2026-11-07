---
description: Final checks and PR description before opening/updating a PR
---

1. Run `just lint`, `just typecheck`, `just test`; fix anything that isn't
   green before continuing.
2. Re-read the hard rules in `AGENTS.md` and confirm the diff violates none
   of them (single-player only, no online/multiplayer code, no Rockstar
   assets or third-party IP, clean-room only, no SDK binaries committed).
3. Write the PR description from `.github/pull_request_template.md`: linked
   issue (`Closes #<n>`), what changed, how it was tested, screenshots (UI
   changes only, before/after), risk, and the single-player-only checkbox.
4. Do not add any AI attribution or `Co-Authored-By` line to the commit or
   PR.
5. Open the PR with `gh pr create` and link it back from the issue.
