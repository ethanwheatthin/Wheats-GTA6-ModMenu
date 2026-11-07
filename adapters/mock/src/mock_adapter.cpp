#include "modmenu/mock/mock_adapter.hpp"

namespace modmenu::mock {

std::optional<EntityHandle> MockGameAdapter::spawn(const SpawnRequest& request) {
  const EntityHandle handle = next_handle_++;
  spawned_entities_[handle] = request;
  return handle;
}

bool MockGameAdapter::delete_entity(EntityHandle handle) {
  return spawned_entities_.erase(handle) > 0;
}

}  // namespace modmenu::mock
