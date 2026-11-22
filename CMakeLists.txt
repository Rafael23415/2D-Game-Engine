cmake_minimum_required(VERSION 3.22)
project(sdl_tutorial LANGUAGES CXX)
 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
 
find_package(SDL3 3.4 CONFIG REQUIRED)   # fails early if SDL is older than 3.4
 
add_executable(
        sdl_tutorial
        src/main.cpp
        src/Scene.h src/Scene.cpp
        src/Program.h src/Program.cpp
        src/InputManager.h src/InputManager.cpp
        src/TextureManager.h src/TextureManager.cpp
        src/SpriteSheet.h src/SpriteSheet.cpp
        src/Vector2D.h src/Vector2D.cpp
        src/Vector2DInt.h src/Vector2DInt.cpp
        src/Actor.h src/Actor.cpp
)
target_link_libraries(sdl_tutorial PRIVATE SDL3::SDL3)
 
if (MSVC)
  target_compile_options(sdl_tutorial PRIVATE /W4)
else()
  target_compile_options(sdl_tutorial PRIVATE -Wall -Wextra -Wpedantic)
endif()
 
# Copy the assets next to the executable after every build.
# (If you create the graphics folder later, run "cmake --preset default" again.)
if (EXISTS ${CMAKE_SOURCE_DIR}/graphics)
  add_custom_command(TARGET sdl_tutorial POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/graphics
            $<TARGET_FILE_DIR:sdl_tutorial>/graphics)
endif()
 
# Run from the executable's folder inside the IDEs, so "graphics/..." is found
set_target_properties(sdl_tutorial PROPERTIES
  VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:sdl_tutorial>"
  XCODE_SCHEME_WORKING_DIRECTORY "$<TARGET_FILE_DIR:sdl_tutorial>")