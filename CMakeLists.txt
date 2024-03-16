cmake_minimum_required(VERSION 3.20)
project(wtmux LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

message(STATUS ${CMAKE_SIZEOF_VOID_P})

Include(FetchContent)

FetchContent_Declare(
 fmt
 GIT_REPOSITORY https://github.com/fmtlib/fmt.git
 GIT_TAG        8.1.1
 GIT_PROGRESS   TRUE )
FetchContent_MakeAvailable(fmt)
include_directories(${fmt_SOURCE_DIR}/include)
set(SE_EXTRA_INCLUDES ${fmt_SOURCE_DIR}/include ${SE_EXTRA_INCLUDES})

FetchContent_Declare(
  argparse
  GIT_REPOSITORY https://github.com/p-ranav/argparse.git
  GIT_TAG        v2.3 )
FetchContent_MakeAvailable(argparse)
include_directories(${argparse_SOURCE_DIR}/include)
set(SE_EXTRA_INCLUDES ${argparse_SOURCE_DIR} ${SE_EXTRA_INCLUDES})

FetchContent_Declare(
  lua
  GIT_REPOSITORY https://github.com/marovira/lua
  GIT_TAG        master )
FetchContent_MakeAvailable(lua)
include_directories(${lua_SOURCE_DIR}/src)
set(SE_EXTRA_INCLUDES ${lua_SOURCE_DIR}/src ${SE_EXTRA_INCLUDES})

FetchContent_Declare(
  sol2
  GIT_REPOSITORY https://github.com/ThePhD/sol2.git
  GIT_TAG        v4.0.0-alpha )
FetchContent_MakeAvailable(sol2)
include_directories(${sol2_SOURCE_DIR}/include)
set(SE_EXTRA_INCLUDES ${sol2_SOURCE_DIR}/include ${SE_EXTRA_INCLUDES})


set(SE_EXTRA_INCLUDES ${SE_EXTRA_INCLUDES} PARENT_SCOPE)
set(EXTERNAL_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty)

include_directories( Source )

add_compile_definitions(NOMINMAX)
add_compile_definitions(_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS)

add_subdirectory( Source )
