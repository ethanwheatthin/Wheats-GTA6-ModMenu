#pragma once

#include <cstdint>
#include <optional>
#include <string>

namespace modmenu {

using EntityHandle = std::uint32_t;
inline constexpr EntityHandle kInvalidHandle = 0;

struct Vector3 {
  float x = 0.0F;
  float y = 0.0F;
  float z = 0.0F;
};

enum class SpawnKind { kVehicle, kPed, kObject };

struct SpawnRequest {
  SpawnKind kind;
  std::string model_name;
  Vector3 position;
  float heading = 0.0F;
};

// GameAdapter is the only boundary through which `core/` talks to a game.
// No implementation of this interface may be called from `core/` outside
// this header's contract, and no game- or Windows-specific headers may leak
// into `core/`. `adapters/mock` and `adapters/gtav` provide implementations.
//
// No exceptions cross this boundary: failures are reported via
// std::optional / bool return values.
class GameAdapter {
 public:
  virtual ~GameAdapter() = default;

  // --- Session -------------------------------------------------------
  // Must return true whenever the local player is in (or entering) an
  // online/multiplayer session. The plugin unloads itself when this is
  // true; see AGENTS.md hard rules.
  virtual bool is_online_session() const = 0;

  // --- Player state ----------------------------------------------------
  virtual void set_player_god_mode(bool enabled) = 0;
  virtual void set_player_never_wanted(bool enabled) = 0;
  virtual std::optional<Vector3> get_player_position() const = 0;

  // --- Spawning ----------------------------------------------------
  virtual std::optional<EntityHandle> spawn(const SpawnRequest& request) = 0;
  virtual bool delete_entity(EntityHandle handle) = 0;

  // --- Teleport ----------------------------------------------------
  virtual bool teleport_player(const Vector3& destination) = 0;

  // --- Weather / time ------------------------------------------------
  virtual bool set_weather(const std::string& weather_name) = 0;
  virtual bool set_time_of_day(int hour, int minute) = 0;

  // --- Weapons ----------------------------------------------------
  virtual bool give_weapon(const std::string& weapon_name, int ammo) = 0;
  virtual bool remove_all_weapons() = 0;

  // --- Camera ----------------------------------------------------
  virtual bool set_free_camera(bool enabled) = 0;

  // --- World ----------------------------------------------------
  virtual bool set_gravity(float gravity) = 0;
  virtual bool set_traffic_density(float density) = 0;

  // --- Animations ----------------------------------------------------
  virtual bool play_animation(EntityHandle handle, const std::string& animation_name) = 0;
};

}  // namespace modmenu
