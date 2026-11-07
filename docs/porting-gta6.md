# Porting to GTA VI

**Portability is unverified.** The `GameAdapter` boundary (see
`docs/adr/0002-game-adapter-boundary.md`) is designed to make this possible,
but nothing here has been tried against real GTA VI PC tooling, because that
tooling doesn't exist yet. Treat this document as a plan, not a guarantee.

## What should carry over largely unchanged

- `core/` — feature registry, menu model, settings, save/load formats. None
  of it depends on GTA V specifically; it only depends on `GameAdapter`.
- UI *logic* in `ui/` — which screens exist, how search/filtering works, how
  the menu model drives rendering. The `RenderHook` abstraction's shape
  should carry over even if its concrete implementation doesn't.
- Save/load formats (map XML, animation sequences, settings files) — these
  are our own formats, independent of the game.
- The test suite structure: `core`'s tests run against a mock adapter today;
  the same tests should run unchanged against a future `adapters/gtavi` mock.

## What will not carry over

- `adapters/gtav` itself: ScriptHookV natives, memory hooks/offsets, and SHV
  glue are entirely GTA V-specific.
- The render hook's concrete implementation (whatever D3D version and
  present-hook technique GTA VI's renderer needs).
- Any assumption baked into `adapters/gtav` about process structure, anti-
  cheat surface, or how online-session detection is implemented — GTA VI's
  equivalent must be re-derived, not assumed to match GTA V's.
- `data/` content that's GTA V-specific (vehicle/ped lists); a GTA VI
  equivalent would need its own clean-room data set.

## Checklist for writing a `gtavi` adapter once PC tooling exists

1. Confirm a modding SDK/hooking approach exists for GTA VI PC and that it's
   legal to use under Rockstar's then-current mod guidelines (re-check them;
   they may change for GTA VI).
2. Add `adapters/gtavi/`, implementing `modmenu::GameAdapter` (extending the
   interface as needed, the same way `adapters/gtav` does today).
3. Re-derive **online-session detection** first, independently — do not
   assume GTA V's technique applies. This is a hard requirement from day one
   (see `AGENTS.md`), same as for GTA V.
4. Port `core/`'s tests to also run against `adapters/gtavi`'s mock
   equivalent (or reuse `adapters/mock` if the interface didn't change).
5. Re-implement the render hook for GTA VI's renderer; keep the `RenderHook`
   interface in `ui/` unless it proves insufficient.
6. Re-scope `docs/specs/menyoo-parity.md`-equivalent feature work: which
   features are still desired, which `GameAdapter` capabilities they need,
   and which are blocked by missing SDK functionality.
7. Re-validate every hard rule in `AGENTS.md` against GTA VI specifically
   (its own mod guidelines, online detection, no story/mission changes,
   etc.) before shipping anything.
