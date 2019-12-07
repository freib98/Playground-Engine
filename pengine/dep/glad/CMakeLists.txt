cmake_minimum_required(VERSION 3.6)

project(glad)

file(GLOB_RECURSE SRC_GLAD
    **/*.c
    **/*.h
    pengine.h)

add_library(${PROJECT_NAME} STATIC ${SRC_GLAD})

target_include_directories(${PROJECT_NAME} PUBLIC include)
