# 2. Game adapter boundary

Date: 2026-11-06

## Status

Accepted

## Context

This mod menu targets GTA V today, but is explicitly meant to be portable to
GTA VI once a PC version and modding tooling exist (see
`docs/porting-gta6.md`). We don't know GTA VI's native API, memory layout, or
even whether ScriptHookV-style hooking will be possible on it. We do know
that menu logic, settings, save/load formats, and the UI's *behavior* (what
"god mode" means, what a saved map contains, etc.) have nothing to do with
which game is running.

Separately, `core/` needs to be testable in CI without the real game, without
ScriptHookV, and without Windows — none of which are available or desirable
in a GitHub Actions runner.

## Decision

All game-specific state and actions are accessed through a single abstract
interface, `modmenu::GameAdapter` (`core/include/modmenu/game_adapter.hpp`).
`core/` depends only on this interface and must not `#include` anything
Windows- or GTA-specific. Two implementations exist:

- `adapters/mock` — in-memory, no real game, used by all tests and CI.
- `adapters/gtav` — the real GTA V implementation (ScriptHookV natives,
  hooks), built only when a developer sets `SHV_SDK_DIR` locally. Never
  built in CI.

A future `adapters/gtavi` would implement the same interface (extended as
needed) once GTA VI tooling exists.

## What is expected to port to GTA VI

- `core/` entirely: feature registry, menu model, settings, save/load
  formats, and any logic expressed purely in terms of `GameAdapter`.
- `ui/`'s ImGui overlay logic and the `RenderHook` abstraction's *shape*
  (the concrete D3D hook implementation will likely need to change).
- The test suite structure (write a `adapters/gtavi` mock-equivalent, reuse
  `core`'s tests against it).

## What will not port

- `adapters/gtav` itself: natives, memory offsets, hook addresses, and SHV
  glue are GTA V-specific and are expected to be rewritten from scratch for
  GTA VI.
- Any assumption about GTA VI's render pipeline, process structure, or
  anti-cheat/online-detection surface.

## Consequences

`core/` stays small, game-agnostic, and fully unit-testable without the SDK,
at the cost of an extra indirection layer and the discipline of never
reaching around `GameAdapter`. Portability to GTA VI is a design goal, not a
guarantee — it is unverified until a `gtavi` adapter is actually attempted.
