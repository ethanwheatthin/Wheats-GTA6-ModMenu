#include "modmenu/mock/mock_adapter.hpp"

#include <gtest/gtest.h>

namespace modmenu::mock {
namespace {

TEST(MockGameAdapter, DefaultsToOfflineSession) {
  MockGameAdapter adapter;
  EXPECT_FALSE(adapter.is_online_session());
}

TEST(MockGameAdapter, OnlineSessionFlagRoundTrips) {
  MockGameAdapter adapter;
  adapter.set_online_session(true);
  EXPECT_TRUE(adapter.is_online_session());
}

TEST(MockGameAdapter, SpawnThenDeleteEntitySucceeds) {
  MockGameAdapter adapter;
  const auto handle = adapter.spawn(SpawnRequest{SpawnKind::kVehicle, "test_car", {}, 0.0F});
  ASSERT_TRUE(handle.has_value());
  EXPECT_TRUE(adapter.delete_entity(*handle));
  EXPECT_FALSE(adapter.delete_entity(*handle));
}

TEST(MockGameAdapter, TeleportUpdatesPlayerPosition) {
  MockGameAdapter adapter;
  const Vector3 destination{1.0F, 2.0F, 3.0F};
  EXPECT_TRUE(adapter.teleport_player(destination));
  const auto position = adapter.get_player_position();
  ASSERT_TRUE(position.has_value());
  EXPECT_FLOAT_EQ(position->x, destination.x);
  EXPECT_FLOAT_EQ(position->y, destination.y);
  EXPECT_FLOAT_EQ(position->z, destination.z);
}

}  // namespace
}  // namespace modmenu::mock
