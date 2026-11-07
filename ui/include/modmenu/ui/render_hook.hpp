#pragma once

namespace modmenu::ui {

// Abstraction over the game's present/render call, so the ImGui overlay
// never depends directly on a specific D3D version or game window.
// Unimplemented - see ui/README.md.
class RenderHook {
 public:
  virtual ~RenderHook() = default;
  virtual bool install() = 0;
  virtual void uninstall() = 0;
};

}  // namespace modmenu::ui
