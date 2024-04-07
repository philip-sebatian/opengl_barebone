cmake_minimum_required(VERSION 3.1)
project(first_graph)
cmake_policy(SET CMP0072 NEW)
find_package(OpenGL REQUIRED)
add_executable(first_graph 
    src/main.cpp
    src/glad.c
    src/glad.h
    
    )
target_link_libraries(first_graph glfw OpenGL::GL)