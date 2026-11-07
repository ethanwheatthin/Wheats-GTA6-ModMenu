# adapters/gtav

Real GTA V `GameAdapter` implementation: ScriptHookV natives, memory hooks,
and SHV glue.

**Unimplemented.** This requires the ScriptHookV SDK, which is not and will
never be committed to this repo (see `AGENTS.md` hard rules). It only builds
when a developer sets `SHV_SDK_DIR` locally, and CI never builds it.

Implementation is tracked by future milestone tickets (M1+), scoped from
`docs/specs/menyoo-parity.md`, once a developer with the SDK picks them up.
