add_library(modmenu_mock_adapter STATIC src/mock_adapter.cpp)
target_include_directories(modmenu_mock_adapter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(modmenu_mock_adapter PUBLIC modmenu_core)
target_compile_options(modmenu_mock_adapter PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Werror>
)
