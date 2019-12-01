cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 17)

project(pengine)

file(GLOB_RECURSE SRC_ENGINE
    **/*.cpp
    **/*.h
    pengine.h)

add_library(${PROJECT_NAME} SHARED ${SRC_ENGINE})
target_include_directories(${PROJECT_NAME} PUBLIC "")

set(root ${CMAKE_CURRENT_SOURCE_DIR})
source_group(TREE ${root} FILES ${SRC_ENGINE})

target_link_libraries(${PROJECT_NAME} PUBLIC glad)
