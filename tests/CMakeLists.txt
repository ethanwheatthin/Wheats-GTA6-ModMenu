include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(modmenu_tests mock_adapter_test.cpp)
target_link_libraries(modmenu_tests PRIVATE modmenu_core modmenu_mock_adapter GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(modmenu_tests)
