cmake_minimum_required(VERSION 3.25)
project(WheatsGTA6ModMenu LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(MODMENU_BUILD_TESTS "Build tests" ON)

if(DEFINED ENV{SHV_SDK_DIR} AND NOT "$ENV{SHV_SDK_DIR}" STREQUAL "")
  set(MODMENU_HAVE_SHV_SDK ON)
else()
  set(MODMENU_HAVE_SHV_SDK OFF)
endif()

add_subdirectory(core)
add_subdirectory(adapters/mock)
add_subdirectory(ui)

if(MODMENU_HAVE_SHV_SDK)
  add_subdirectory(adapters/gtav)
  add_subdirectory(plugin)
else()
  message(STATUS "SHV_SDK_DIR not set - skipping adapters/gtav and plugin (core + mock adapter only)")
endif()

if(MODMENU_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
