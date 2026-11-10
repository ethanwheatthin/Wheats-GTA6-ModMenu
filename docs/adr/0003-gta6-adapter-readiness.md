# 3. GTA VI adapter readiness

Date: 2026-11-10

## Status

Accepted

## Context

GTA VI's console pre-load went live on 2026-11-09 ahead of a 2026-11-19
console launch. Rockstar has announced no PC release date, storefront, or
system requirements. Public data mining so far reads encrypted package
metadata only (file names, chunk counts, install size); it exposes nothing
about scripting, natives, or memory layout, and none of it applies to a PC
executable that does not exist yet.

Two public hints matter to us:

- Reports describe a shared base install with story content packaged
  separately, plus a `launchMultiplayerActivity` metadata string. This is
  unconfirmed interpretation, but it reinforces that the online-session
  detection and self-unload requirement in `AGENTS.md` must be re-derived
  for GTA VI, not copied from GTA V.
- Nothing public shows a GTA VI script hook, native list, or RAGE tooling.

We use only public reporting as background. We do not use ripped or dumped
game files, and we do not depend on any claim above being true.

## Decision

1. Do not start `adapters/gtavi` until PC tooling exists and Rockstar's
   then-current mod guidelines permit it.
2. Keep `GameAdapter` free of GTA V assumptions and enforce that with
   contract tests that any future adapter must pass
   (`tests/adapter_contract_test.cpp`).
3. Track readiness with the checklist below.

## Audit of `GameAdapter` for GTA V assumptions

Already game-agnostic: models, weapons, weather, and animations are passed as
strings (no GTA V hashes); failures use `std::optional` / `bool`; online
detection lives on the interface.

Residual risks, to revisit when a real GTA VI adapter is attempted:

- **Handle width.** `EntityHandle` is `std::uint32_t`. GTA VI may need a wider
  handle. Contract: handles are opaque and never `kInvalidHandle`. Widening
  later is a mechanical change if callers never inspect the value.
- **Vocabulary.** Weather names, model names, and animation names are
  adapter-defined strings. The mock's default weather `"CLEAR"` is only a
  placeholder. `core/` must not hard-code GTA V names.
- **Capability discovery.** Every method is pure virtual, so an adapter that
  cannot support a feature can only return `false`; the menu cannot hide it.
  If GTA VI lacks a feature, add a capability query (with a mock
  implementation first, per `AGENTS.md`).
- **Single player entity.** The interface assumes one local player. GTA VI is
  publicly described as having two protagonists; whether that needs a
  "which character" concept is unknown until tooling exists.
- **Coordinates.** `Vector3` is a Z-up float triple. Treat that as unverified
  for GTA VI.
- **Input validation.** Previously only implicit. `set_time_of_day` now
  documents and enforces range checks, and the mock rejects invalid values.

## Readiness checklist (to start `adapters/gtavi`)

- [ ] Rockstar announces a PC release (date, storefront).
- [ ] A hooking or scripting approach for GTA VI PC exists and is legal under
      Rockstar's current mod guidelines (re-read them).
- [ ] Online-session detection is re-derived independently, with a test.
- [ ] A `gtavi` mock or reuse of `adapters/mock` passes the contract tests.
- [ ] Render hook strategy chosen for GTA VI's renderer.
- [ ] `data/` gets a clean-room GTA VI data set (no Rockstar assets).
- [ ] Every hard rule in `AGENTS.md` re-validated for GTA VI.

Things to watch: Rockstar Newswire PC announcements, statements from
existing hook-library authors about GTA VI support, and any official mod
policy for GTA VI.

## Consequences

Low cost now: one ADR, a small contract test suite, and clearer interface
docs. The work stays honest about what is unknown; it does not claim
portability, which remains unverified (see `docs/porting-gta6.md`).
