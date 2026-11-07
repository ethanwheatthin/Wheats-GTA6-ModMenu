# Only reached when SHV_SDK_DIR is set (see top-level CMakeLists.txt).
# Never built in CI. Unimplemented - see plugin/src/dllmain.cpp.
add_library(modmenu SHARED src/dllmain.cpp)
set_target_properties(modmenu PROPERTIES SUFFIX ".asi")
target_link_libraries(modmenu PRIVATE modmenu_core modmenu_gtav_adapter modmenu_ui)
