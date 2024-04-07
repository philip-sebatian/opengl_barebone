cmake_minimum_required(VERSION 3.1)
project(first_graph)
cmake_policy(SET CMP0072 NEW)
include_directories(src dependencies)
find_package(OpenGL REQUIRED)
add_executable(first_graph 
    src/main.cpp
    src/glad.c
    
    
    )
target_link_libraries(first_graph glfw OpenGL::GL)