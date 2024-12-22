cmake_minimum_required(VERSION 3.15)

project(OpenGL_Journey VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

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


file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(OpenGL_Journey 
    ${SOURCES}
        src/Camera.cpp
        src/include/Camera.h
)
add_compile_definitions(SHADER_DIR="${SHADER_DIR}")
set_target_properties(OpenGL_Journey PROPERTIES OUTPUT_NAME "app")

target_include_directories(OpenGL_Journey PRIVATE ${CMAKE_SOURCE_DIR}/external/GLM ${CMAKE_SOURCE_DIR}/src/include)

target_link_libraries(OpenGL_Journey
    glfw3
    glew32
    opengl32
    gdi32
    glm
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(OpenGL_Journey PRIVATE -g)
endif()