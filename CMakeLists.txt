cmake_minimum_required(VERSION 3.30)

project(OpenGL_Journey VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe")
set(SHADER_DIR "${CMAKE_SOURCE_DIR}/src/shaders")


include_directories(
    ${CMAKE_SOURCE_DIR}/external/GLEW/include
    ${CMAKE_SOURCE_DIR}/external/GLFW/include
    ${CMAKE_SOURCE_DIR}/src/include
)

link_directories(
    ${CMAKE_SOURCE_DIR}/external/GLEW/lib
    ${CMAKE_SOURCE_DIR}/external/GLFW/lib
)

add_subdirectory(external/GLM)
add_definitions(-DSHADER_DIR="${CMAKE_SOURCE_DIR}/src/shaders")


file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(OpenGL_Journey ${SOURCES})
set_target_properties(OpenGL_Journey PROPERTIES OUTPUT_NAME "app")

target_include_directories(OpenGL_Journey PRIVATE ${CMAKE_SOURCE_DIR}/external/GLM ${CMAKE_SOURCE_DIR}/src/include)

target_link_libraries(OpenGL_Journey
    glfw3
    glew32
    opengl32
    gdi32
    glm
)
target_compile_definitions(OpenGL_Journey PRIVATE SHADER_DIR="${SHADER_DIR}/")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(OpenGL_Journey PRIVATE -g)
endif()