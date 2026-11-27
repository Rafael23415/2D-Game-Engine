cmake_minimum_required(VERSION 3.25)
project(Engineering2D LANGUAGES C CXX)
 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# --- Dependencies ---------------------------------------------------------

find_package(OpenGL REQUIRED)
find_package(SDL3 3.4 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# --- Application ----------------------------------------------------------
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/TestActor.h src/TestActor.cpp
        src/Core/Vertex.shader src/Core/Fragment.shader
        src/Core/Scene.h src/Core/Scene.cpp
        src/Core/Graphics.h src/Core/Graphics.cpp
        src/Core/InputManager.h src/Core/InputManager.cpp
        src/Core/TextureManager.h src/Core/TextureManager.cpp 
        src/Core/Actor.h src/Core/Actor.cpp
        src/Math/Vector2D.h src/Math/Vector2D.cpp
        src/Math/Vector2DInt.h src/Math/Vector2DInt.cpp
        src/Debug/Debug.h
        src/External/stb_image.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE src/Core src/Math src/Debug src/External)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 glad::glad glm::glm OpenGL::GL)
 
if (MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# --- Assets ---------------------------------------------------------------
# Copy the assets next to the executable after every build.
# (If you create the assets folder later, run "cmake --preset default" again.)
if (EXISTS ${CMAKE_SOURCE_DIR}/assets)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
	    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)
endif()

# --- IDE settings ---------------------------------------------------------
# Run from the executable's folder inside the IDEs, so "assets/..." is found
set_target_properties(${PROJECT_NAME} PROPERTIES
  VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
  XCODE_SCHEME_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})