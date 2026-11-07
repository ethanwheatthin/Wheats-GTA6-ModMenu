#pragma once

#include "modmenu/game_adapter.hpp"

namespace modmenu::gtav {

// Real GTA V adapter. Unimplemented - see adapters/gtav/README.md.
// Intentionally does not derive from GameAdapter yet: no method here should
// be implemented until a ticket does so against the real SHV SDK.
class GtavAdapter {
 public:
  GtavAdapter() = delete;
};

}  // namespace modmenu::gtav
