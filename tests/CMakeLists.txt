include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(modmenu_tests mock_adapter_test.cpp adapter_contract_test.cpp)
target_link_libraries(modmenu_tests PRIVATE modmenu_core modmenu_mock_adapter GTest::gtest_main)
target_compile_definitions(modmenu_tests PRIVATE
  MODMENU_CORE_INCLUDE_DIR="${PROJECT_SOURCE_DIR}/core/include")
target_compile_options(modmenu_tests PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Werror>
)

include(GoogleTest)
gtest_discover_tests(modmenu_tests)
