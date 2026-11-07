# Only reached when SHV_SDK_DIR is set (see top-level CMakeLists.txt).
# Unimplemented placeholder - see README.md.
add_library(modmenu_gtav_adapter STATIC src/gtav_adapter.cpp)
target_include_directories(modmenu_gtav_adapter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(modmenu_gtav_adapter PUBLIC modmenu_core)
target_include_directories(modmenu_gtav_adapter PRIVATE "$ENV{SHV_SDK_DIR}")
