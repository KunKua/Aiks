cmake_minimum_required(VERSION 2.8)
# It ensures that when Find*.cmake files included from cmake's Modules dir
# include another *.cmake file with relative path, that file will be included
# also from cmake's Modules dir, to not clash with per-project files.
cmake_policy(SET CMP0017 NEW)

# Use new behaviour with cmake >= 3.1:
# Only interpret if() arguments as variables or keywords when unquoted.
if(CMAKE_VERSION VERSION_GREATER 3.1)
    cmake_policy(SET CMP0054 NEW)
endif()

project (Aiks)

# The version number
set(AIKS_VERSION 1.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

message(${BUILDING_STRING})

set(USE_WEBP_DEFAULT ON)
if(WINRT OR WP8)
  set(USE_WEBP_DEFAULT OFF)
endif()

set(USE_PREBUILT_LIBS_DEFAULT ON)
if(MINGW)
  set(USE_PREBUILT_LIBS_DEFAULT OFF)
endif()

set(BUILD_CPP_TESTS_DEFAULT ON)
set(BUILD_LUA_LIBS_DEFAULT ON)
set(BUILD_LUA_TESTS_DEFAULT ON)
set(BUILD_JS_LIBS_DEFAULT ON)
set(BUILD_JS_TESTS_DEFAULT ON)
# TODO: fix test samples for MSVC
if(MSVC)
  set(BUILD_CPP_TESTS_DEFAULT OFF)
  set(BUILD_LUA_LIBS_DEFAULT OFF)
  set(BUILD_LUA_TESTS_DEFAULT OFF)
  set(BUILD_JS_LIBS_DEFAULT OFF)
  set(BUILD_JS_TESTS_DEFAULT OFF)
endif()
