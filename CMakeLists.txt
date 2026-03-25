cmake_minimum_required(VERSION 3.24)

project(game)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-g -Wall -Wextra -pedantic)
#add_compile_options(-g -Wall -Wextra -pedantic -flto -O3)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BUILD_SHARED_LIBS ON)

# On Windows, create dll's in the same directory as the game executable
if (WIN32)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

include(FetchContent)

# 1. ALWAYS Declare the potential dependencies first
FetchContent_Declare(
    SDL
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.0
    GIT_SHALLOW TRUE
    OVERRIDE_FIND_PACKAGE
)

FetchContent_Declare(
    SDL_mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG main
    GIT_SHALLOW TRUE
    OVERRIDE_FIND_PACKAGE
)

# 2. Check for SDL3 Core
find_package(SDL3 QUIET)
if(NOT SDL3_FOUND)
    message(STATUS "SDL3 not found - building from source")
    FetchContent_MakeAvailable(SDL)
endif()

# 3. Check for SDL3 Mixer
find_package(SDL3_mixer QUIET)
if(NOT SDL3_mixer_FOUND)
    message(STATUS "SDL3_mixer not found - building from source")
    
    # Configure Mixer options BEFORE making it available
    set(SDLMIXER_MIDI_NATIVE OFF CACHE BOOL "" FORCE)
    set(SDLMIXER_GME OFF CACHE BOOL "" FORCE)
    set(SDLMIXER_WAVPACK OFF CACHE BOOL "" FORCE)
    set(SDLMIXER_MOD OFF CACHE BOOL "" FORCE)
    set(SDLMIXER_OPUS OFF CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(SDL_mixer)
endif()

# --- Rest of your project ---
add_subdirectory(utility)
add_subdirectory(graphics)
add_subdirectory(world)

add_library(game_lib
    game.cpp game.h
    asset_manager.cpp asset_manager.h
    level_designer.cpp level_designer.h
)

target_link_libraries(game_lib PUBLIC SDL3::SDL3 SDL3_mixer::SDL3_mixer graphics world)

add_executable(game main.cpp)
target_link_libraries(game PUBLIC game_lib)

add_executable(level_designer main_designer.cpp)
target_link_libraries(level_designer PUBLIC game_lib)