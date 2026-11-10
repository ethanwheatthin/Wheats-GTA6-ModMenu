#pragma once

#include <unordered_map>

#include "modmenu/game_adapter.hpp"

namespace modmenu::mock {

// In-memory, no-op implementation of GameAdapter used by tests and CI.
// Test-only setters (set_online_session, etc.) let tests drive state that a
// real adapter would read from the game process.
class MockGameAdapter final : public GameAdapter {
 public:
  bool is_online_session() const override { return online_session_; }
  void set_online_session(bool online) { online_session_ = online; }

  void set_player_god_mode(bool enabled) override { god_mode_ = enabled; }
  bool god_mode() const { return god_mode_; }

  void set_player_never_wanted(bool enabled) override { never_wanted_ = enabled; }
  bool never_wanted() const { return never_wanted_; }

  std::optional<Vector3> get_player_position() const override { return player_position_; }
  void set_player_position(const Vector3& position) { player_position_ = position; }

  std::optional<EntityHandle> spawn(const SpawnRequest& request) override;
  bool delete_entity(EntityHandle handle) override;

  bool teleport_player(const Vector3& destination) override {
    player_position_ = destination;
    return true;
  }

  bool set_weather(const std::string& weather_name) override {
    weather_ = weather_name;
    return true;
  }
  const std::string& weather() const { return weather_; }

  bool set_time_of_day(int hour, int minute) override {
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
      return false;
    }
    hour_ = hour;
    minute_ = minute;
    return true;
  }

  bool give_weapon(const std::string& /*weapon_name*/, int /*ammo*/) override { return true; }
  bool remove_all_weapons() override { return true; }

  bool set_free_camera(bool enabled) override {
    free_camera_ = enabled;
    return true;
  }

  bool set_gravity(float gravity) override {
    gravity_ = gravity;
    return true;
  }

  bool set_traffic_density(float density) override {
    traffic_density_ = density;
    return true;
  }

  bool play_animation(EntityHandle /*handle*/, const std::string& /*animation_name*/) override {
    return true;
  }

 private:
  bool online_session_ = false;
  bool god_mode_ = false;
  bool never_wanted_ = false;
  bool free_camera_ = false;
  float gravity_ = 1.0F;
  float traffic_density_ = 1.0F;
  int hour_ = 12;
  int minute_ = 0;
  std::string weather_ = "CLEAR";
  std::optional<Vector3> player_position_;
  std::unordered_map<EntityHandle, SpawnRequest> spawned_entities_;
  EntityHandle next_handle_ = 1;
};

}  // namespace modmenu::mock
