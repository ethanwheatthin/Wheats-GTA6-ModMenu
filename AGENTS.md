# Wheats-GTA6-ModMenu — agent instructions

Source of truth for any coding agent (human or AI) working in this repo.

## What this is

A free, non-commercial, **single-player-only** PC mod menu for GTA V
(Menyoo-style trainer, clean-room), structured so the game layer can be
swapped for GTA VI once a PC version and tooling exist.

## Stack

- C++20, CMake + Ninja (presets: `dev`, `release`, `ci`)
- Dear ImGui overlay
- GoogleTest
- clang-format + clang-tidy, `pre-commit`
- Output: an `.asi` plugin (a DLL loaded by an ASI loader)
- Target: Windows x64. CI runs on `windows-latest`.

## Folder structure

- `core/` — game-agnostic library: feature registry, menu model, settings,
  save/load formats. **Zero** game or Windows-hook dependencies. Talks to the
  game only through `core/include/modmenu/game_adapter.hpp`.
- `adapters/gtav/` — GTA V adapter (natives, hooks, SHV glue). Built only when
  `SHV_SDK_DIR` is set.
- `adapters/mock/` — mock adapter used by tests and CI. Always builds.
- `ui/` — ImGui overlay and render hook abstraction.
- `plugin/` — builds the `.asi` entry point.
- `tests/` — GoogleTest suites, run against the mock adapter.
- `docs/` — specs, ADRs, setup/workflow docs.
- `scripts/` — `dev`, `build`, `lint`, `typecheck`, `test` helpers.
- `data/` — our own entity/vehicle lists, clean-room, no Rockstar assets.

## Commands

| Task | Command |
|---|---|
| Configure (dev) | `cmake --preset dev` |
| Build | `scripts/build.ps1` / `scripts/build.sh` (ctest target via ninja) |
| Lint | `scripts/lint.ps1` (clang-format `--dry-run --Werror` + clang-tidy) |
| Typecheck | `scripts/typecheck.ps1` (compile-only, `-Werror`) |
| Test | `scripts/test.ps1` (`ctest --preset ci`) |

All of the above must be green against the mock adapter with **no SDK present**.

## Coding conventions

- C++20, no exceptions across the `GameAdapter` boundary (return
  `std::optional`/status codes instead).
- `core/` must not `#include` anything Windows- or GTA-specific.
- Format with `.clang-format` (run via `pre-commit` or `scripts/lint`).
- Follow `.clang-tidy` warnings; do not disable checks inline without a
  one-line comment explaining why.

## Testing rules

- Every behavioral change needs a test.
- Core logic is tested exclusively against `adapters/mock`; never require the
  real SHV SDK for tests.
- New `GameAdapter` capabilities need a mock implementation before anything
  else can depend on them.

## Git rules

- Branch naming: `agent/<issue#>-<slug>`.
- [Conventional Commits](https://www.conventionalcommits.org/) for every
  commit message (`feat:`, `fix:`, `docs:`, `chore:`, `test:`, ...).
- Every PR must reference `Closes #<n>`.
- **No AI attribution or `Co-Authored-By` lines in commits or PRs.**
- Never push to `main`. Never merge your own PR.
- Never edit CI, secrets, or workflow files without adding the
  `needs-human` label and stopping for a human to review.
- If blocked or requirements are ambiguous, stop and comment on the issue —
  do not guess.

## Definition of done

1. Acceptance criteria from the issue are met.
2. Tests added/updated and passing against the mock adapter.
3. `lint`, `typecheck`, `test` all green.
4. No hard rule (below) violated.
5. PR opened referencing the issue, with what changed / how it was tested.
6. Card moved to "In Review".

## Hard rules (non-negotiable)

Based on
[Rockstar's published mod guidelines](https://www.rockstargames.com/community-resources/mod-guidelines).
Re-read them if available and flag anything that conflicts.

- Single-player/Story Mode only. No online features, no multiplayer, no code
  that touches online services.
- The plugin must detect online mode and unload itself. This is a hard
  requirement from day one, with a test for the detection logic.
- Free and non-commercial. No payments, no paid features.
- No Rockstar assets, no ripped game files, no third-party IP, no extending
  or modifying the official story or missions.
- Clean-room only: **do not read, copy, or paraphrase Menyoo's source code**
  (it is GPLv3). Work only from the feature list in
  `docs/specs/menyoo-parity.md` and observed behavior.
- Do not commit ScriptHookV or any third-party SDK/binaries. The developer
  supplies the SDK path locally via `SHV_SDK_DIR`. CI builds only the core
  library and tests against the mock adapter.
- Never push to `main`, never merge, never edit CI/secrets/workflows without
  a `needs-human` flag. Stop and comment on the issue when blocked or
  requirements are ambiguous.
