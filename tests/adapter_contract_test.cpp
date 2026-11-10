// Contract tests for the GameAdapter boundary.
//
// These are written as typed tests so a future adapter (e.g. a GTA VI mock)
// can be added to `AdapterTypes` and must satisfy the same contract. They
// deliberately avoid any assumption about a specific game's handle values,
// model/weather naming, or coordinate conventions.

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <set>
#include <sstream>
#include <string>

#include "modmenu/game_adapter.hpp"
#include "modmenu/mock/mock_adapter.hpp"

namespace modmenu {
namespace {

template <typename T>
class AdapterContractTest : public ::testing::Test {
 protected:
  T adapter;
};

using AdapterTypes = ::testing::Types<mock::MockGameAdapter>;
TYPED_TEST_SUITE(AdapterContractTest, AdapterTypes);

TYPED_TEST(AdapterContractTest, SpawnNeverReturnsInvalidHandle) {
  const auto handle = this->adapter.spawn(SpawnRequest{SpawnKind::kPed, "any_model", {}, 0.0F});
  ASSERT_TRUE(handle.has_value());
  EXPECT_NE(*handle, kInvalidHandle);
}

TYPED_TEST(AdapterContractTest, SpawnReturnsDistinctHandles) {
  std::set<EntityHandle> seen;
  for (int i = 0; i < 16; ++i) {
    const auto handle =
        this->adapter.spawn(SpawnRequest{SpawnKind::kObject, "any_model", {}, 0.0F});
    ASSERT_TRUE(handle.has_value());
    EXPECT_TRUE(seen.insert(*handle).second) << "duplicate handle " << *handle;
  }
}

TYPED_TEST(AdapterContractTest, DeletingInvalidOrUnknownHandleFails) {
  EXPECT_FALSE(this->adapter.delete_entity(kInvalidHandle));
  EXPECT_FALSE(this->adapter.delete_entity(0xDEADBEEFU));
}

TYPED_TEST(AdapterContractTest, TimeOfDayRejectsOutOfRangeValues) {
  EXPECT_TRUE(this->adapter.set_time_of_day(0, 0));
  EXPECT_TRUE(this->adapter.set_time_of_day(23, 59));
  EXPECT_FALSE(this->adapter.set_time_of_day(24, 0));
  EXPECT_FALSE(this->adapter.set_time_of_day(-1, 0));
  EXPECT_FALSE(this->adapter.set_time_of_day(12, 60));
  EXPECT_FALSE(this->adapter.set_time_of_day(12, -1));
}

TYPED_TEST(AdapterContractTest, OnlineSessionIsReportedWithoutOtherSetup) {
  // Online detection must work on a freshly constructed adapter; the plugin
  // relies on it before any feature is touched (AGENTS.md hard rule).
  EXPECT_FALSE(this->adapter.is_online_session());
}

// core/ must stay free of game- and Windows-specific includes so the
// boundary holds for any future game, not just GTA V.
TEST(CoreHeaderHygiene, NoGameOrWindowsIncludesInCore) {
  const std::filesystem::path root{MODMENU_CORE_INCLUDE_DIR};
  ASSERT_TRUE(std::filesystem::exists(root)) << root;

  const std::set<std::string> forbidden = {
      "windows.h", "Windows.h", "d3d11.h", "d3d12.h", "dxgi.h",
      "main.h",    "natives.h", "types.h", "enums.h",
  };

  for (const auto& entry : std::filesystem::recursive_directory_iterator(root)) {
    if (!entry.is_regular_file()) {
      continue;
    }
    std::ifstream file(entry.path());
    std::string line;
    while (std::getline(file, line)) {
      const auto pos = line.find("#include");
      if (pos == std::string::npos) {
        continue;
      }
      for (const auto& name : forbidden) {
        EXPECT_EQ(line.find(name, pos), std::string::npos)
            << entry.path() << " includes forbidden header: " << line;
      }
    }
  }
}

}  // namespace
}  // namespace modmenu
