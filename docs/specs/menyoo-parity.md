# Menyoo parity feature checklist (clean-room)

Sourced only from public descriptions of Menyoo's behavior and observed
in-game behavior — **never** from Menyoo's source (GPLv3). See `AGENTS.md`'s
clean-room hard rule. Each item has an ID, a one-line behavior description,
and the `GameAdapter` capability it needs (capabilities not yet on the
interface are added when the ticket that needs them is picked up).

Status: `[ ]` not started, `[x]` done. Create issues from this list; don't
pre-create issues beyond the sample ticket unless asked.

## M1 — Menu shell + player + teleport

### Menu/UI

- [ ] `UI-01` Keyboard navigation through menu/submenu lists — core menu model only
- [ ] `UI-02` Controller navigation (same model as `UI-01`) — core menu model only
- [ ] `UI-03` Configurable "open menu" key/button — core menu model + settings
- [ ] `UI-04` Settings/theme screen (colors, font scale) — settings persistence
- [ ] `UI-05` Search box filtering spawn menu lists (vehicles/peds/objects) — core menu model only

### Player

- [ ] `PLR-01` God mode toggle — `set_player_god_mode`
- [ ] `PLR-02` Never wanted toggle — `set_player_never_wanted`
- [ ] `PLR-03` Super run / super jump / super swim toggles — new adapter capability (movement modifiers)
- [ ] `PLR-04` Ragdoll enable/disable toggle — new adapter capability (ragdoll control)
- [ ] `PLR-05` Player height changer — new adapter capability (model/scale)
- [ ] `PLR-06` Player model changer — new adapter capability (ped model swap)
- [ ] `PLR-07` Outfit / component changer (clothing slots) — new adapter capability (ped components)
- [ ] `PLR-08` **Online-session guard**: detect online/multiplayer session and unload the plugin — `is_online_session` (hard requirement, see `AGENTS.md`)

### Teleport

- [ ] `TP-01` Teleport to waypoint — `teleport_player`
- [ ] `TP-02` Teleport to map marker — `teleport_player` + marker list (new)
- [ ] `TP-03` Custom teleport slots (save/recall positions) — `teleport_player` + settings persistence

## M2 — Vehicles

- [ ] `VEH-01` Vehicle spawner with category browsing — `spawn`
- [ ] `VEH-02` DLC filter in spawner — `spawn` + vehicle metadata (new, from `data/`)
- [ ] `VEH-03` Stat filter (speed/accel/braking/traction/seats) — vehicle metadata (new)
- [ ] `VEH-04` Stat panel display for selected vehicle — vehicle metadata (new)
- [ ] `VEH-05` Tuning/customs menu (performance parts) — new adapter capability (vehicle mods)
- [ ] `VEH-06` Paint/livery changer — new adapter capability (vehicle mods)
- [ ] `VEH-07` Neon: flash mode — new adapter capability (vehicle neon)
- [ ] `VEH-08` Neon: fade mode — new adapter capability (vehicle neon)
- [ ] `VEH-09` Neon: RGB cycle mode — new adapter capability (vehicle neon)
- [ ] `VEH-10` Repair vehicle — new adapter capability (vehicle repair)
- [ ] `VEH-11` Boost / nitro — new adapter capability (vehicle boost)
- [ ] `VEH-12` On-screen speedometer — `get_player_position`-style read of current vehicle speed (new)
- [ ] `VEH-13` Cruise control — vehicle speed/throttle control (new)
- [ ] `VEH-14` Hydraulics control — new adapter capability (vehicle suspension)
- [ ] `VEH-15` Add-on vehicle support (vehicles not in base game data) — `data/` vehicle list extensibility

## M3 — Peds / weapons

### Peds

- [ ] `PED-01` Ped spawner — `spawn`
- [ ] `PED-02` Bodyguard/companion spawn + follow behavior — `spawn` + relationship/task capability (new)
- [ ] `PED-03` Task assignment (e.g. wander, guard, combat) — new adapter capability (ped tasks)
- [ ] `PED-04` Relationship group assignment — new adapter capability (relationship groups)
- [ ] `PED-05` Animation playback on a ped — `play_animation`
- [ ] `PED-06` Save a played animation sequence — settings/save-format persistence
- [ ] `PED-07` Load a saved animation sequence — settings/save-format persistence
- [ ] `PED-08` Scenario playback (e.g. sit, lean, idle animations tied to world scenarios) — new adapter capability (scenarios)

### Weapons

- [ ] `WPN-01` Give weapon — `give_weapon`
- [ ] `WPN-02` Remove weapon(s) — `remove_all_weapons`
- [ ] `WPN-03` Set ammo count — new adapter capability (ammo control)
- [ ] `WPN-04` Weapon attachments (scope/grip/suppressor/etc.) — new adapter capability (weapon components)
- [ ] `WPN-05` Weapon tint/camo — new adapter capability (weapon components)
- [ ] `WPN-06` Per-weapon special abilities (e.g. explosive rounds) — new adapter capability (weapon abilities)

## M4 — Object / map editor (spooner)

- [ ] `OBJ-01` Spawn an object/prop — `spawn`
- [ ] `OBJ-02` Move/rotate/scale with live preview — new adapter capability (object transform)
- [ ] `OBJ-03` Attach object to another entity — new adapter capability (attach)
- [ ] `OBJ-04` Freeze object in place (ignore physics) — new adapter capability (freeze)
- [ ] `OBJ-05` Copy/duplicate an object — `spawn` reusing existing transform
- [ ] `OBJ-06` Save current map (our own XML format) — settings/save-format persistence
- [ ] `OBJ-07` Load a saved map — settings/save-format persistence + `spawn`
- [ ] `OBJ-08` Import a user-supplied prop list file — `data/` loader (own format, no Rockstar assets)

## M5 — World / camera / polish

### World

- [ ] `WLD-01` Weather selector — `set_weather`
- [ ] `WLD-02` Time of day control — `set_time_of_day`
- [ ] `WLD-03` Traffic density control — `set_traffic_density`
- [ ] `WLD-04` Population (pedestrian) density control — new adapter capability (population density)
- [ ] `WLD-05` Gravity control — `set_gravity`
- [ ] `WLD-06` Interior / DLC location loader (teleport into interiors) — `teleport_player` + interior list (new)

### Camera

- [ ] `CAM-01` Free camera toggle — `set_free_camera`
- [ ] `CAM-02` Cutscene/camera tools (fixed camera paths, FOV) — new adapter capability (camera tools)

### Misc

- [ ] `MISC-01` Logging to a local file — no adapter dependency (core-only)
- [ ] `MISC-02` Config file (persisted settings) — settings persistence
- [ ] `MISC-03` Hot reload of the plugin without restarting the game — plugin-level, no `core` dependency
