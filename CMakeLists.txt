cmake_minimum_required(VERSION 3.11)

project(minimal CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
set(INCLUDE "${CMAKE_CURRENT_LIST_DIR}/include/")
add_executable(mini_dungeon ${SOURCES})
target_include_directories(mini_dungeon PUBLIC ${INCLUDE})
target_link_libraries(mini_dungeon PUBLIC raylib)

add_custom_command(
    TARGET mini_dungeon POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_LIST_DIR}/assets"
    "$<TARGET_FILE_DIR:mini_dungeon>/assets"
)

target_compile_definitions(mini_dungeon PUBLIC ASSETS_PATH="./assets")

option(ENABLE_DEBUG "Enable debug options" OFF)
if (ENABLE_DEBUG)
  target_compile_definitions(mini_dungeon PUBLIC DEBUG_OPTIONS)
endif()
