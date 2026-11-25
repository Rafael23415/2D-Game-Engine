cmake_minimum_required(VERSION 3.25)
project(2d-game-engine LANGUAGES C CXX)
 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# --- Dependencies ---------------------------------------------------------

add_subdirectory(external/glad)
find_package(OpenGL REQUIRED)
find_package(SDL3 3.4 CONFIG REQUIRED)   # fails early if SDL is older than 3.4

# --- Application ----------------------------------------------------------
add_executable(${PROJECT_NAME}
        src/main.cpp
	    src/stb_image.cpp
        src/Debug.h src/Debug.cpp
        src/Scene.h src/Scene.cpp
        src/Graphics.h src/Graphics.cpp
        src/InputManager.h src/InputManager.cpp
        src/TextureManager.h src/TextureManager.cpp
        src/Vector2D.h src/Vector2D.cpp
        src/Vector2DInt.h src/Vector2DInt.cpp
        src/TestActor.h src/TestActor.cpp
        src/Actor.h src/Actor.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 glad OpenGL::GL)
 
if (MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# --- Assets ---------------------------------------------------------------
# Copy the assets next to the executable after every build.
# (If you create the graphics folder later, run "cmake --preset default" again.)
if (EXISTS ${CMAKE_SOURCE_DIR}/graphics)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/graphics
	    $<TARGET_FILE_DIR:${PROJECT_NAME}>/graphics)
endif()

# --- IDE settings ---------------------------------------------------------
# Run from the executable's folder inside the IDEs, so "graphics/..." is found
set_target_properties(${PROJECT_NAME} PROPERTIES
  VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
  XCODE_SCHEME_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

set_target_properties(glad PROPERTIES FOLDER "external")
if(TARGET SDL3-static)
    set_target_properties(SDL3-static PROPERTIES FOLDER "external")
endif()