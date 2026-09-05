cmake_minimum_required(VERSION 3.24)
project(DungeonRun LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-3.2.22
  GIT_SHALLOW TRUE
)
set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL3)

add_executable(dungeon_run
  src/main.cpp
  src/app/App.cpp
  src/game/Game.cpp
  src/render/Renderer.cpp
)

target_include_directories(dungeon_run PRIVATE src)
target_link_libraries(dungeon_run PRIVATE SDL3::SDL3)

# Keep the shared SDL3 runtime next to the exe for easy local runs.
add_custom_command(
  TARGET dungeon_run
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL3::SDL3>
    $<TARGET_FILE_DIR:dungeon_run>
)

if(MSVC)
  target_compile_options(dungeon_run PRIVATE /W4)
else()
  target_compile_options(dungeon_run PRIVATE -Wall -Wextra -Wpedantic)
endif()
