# Dear ImGui is not vendored yet - see README.md. This is header-only until
# an M1 ticket pulls in ImGui via FetchContent and adds overlay sources.
add_library(modmenu_ui INTERFACE)
target_include_directories(modmenu_ui INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(modmenu_ui INTERFACE modmenu_core)
