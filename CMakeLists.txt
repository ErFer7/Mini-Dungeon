cmake_minimum_required(VERSION 3.14)

project(minimal CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(raylib)

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
