cmake_minimum_required(VERSION 3.01)
project(LearnOpenGL)

include_directories(
    ${PROJECT_SOURCE_DIR}/dependencies
    ${PROJECT_SOURCE_DIR}/dependencies/glad
    ${PROJECT_SOURCE_DIR}/dependencies/GLFW
    ${PROJECT_SOURCE_DIR}/dependencies/stb
)

add_library(glad ${PROJECT_SOURCE_DIR}/dependencies/glad/glad.c)

link_directories(${PROJECT_SOURCE_DIR}/dependencies/GLFW)

add_executable(LearnOpenGL src/main.cpp)

target_link_libraries (LearnOpenGL glad)
target_link_libraries (LearnOpenGL glfw3.lib)