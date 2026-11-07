# ui

Dear ImGui overlay and the render-hook abstraction it's drawn through.

Dear ImGui itself is not vendored yet. When a milestone M1 ticket starts
implementing the overlay, pull it in via CMake `FetchContent` (MIT-licensed,
no clean-room concern) rather than hand-copying files.

`render_hook.hpp` is the abstraction `core`/`ui` code depends on instead of
talking to D3D/the game window directly, so the real hook (D3D11/D3D12
present hook) stays swappable per-game, same as `GameAdapter`.
