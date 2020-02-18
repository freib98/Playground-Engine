cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 17)

project(pengine)

# ------------------------------------------------------------
# Add PEngine
# ------------------------------------------------------------

file(GLOB_RECURSE SRC_ENGINE
    core/*.cpp
    core/*.h
    platform/*.cpp
    platform/*.h
    renderer/*.cpp
    renderer/*.h
    pengine.h)

add_library(${PROJECT_NAME} STATIC ${SRC_ENGINE})
target_include_directories(${PROJECT_NAME} PUBLIC "")

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_ENGINE})

# ------------------------------------------------------------
# Add spdlog
# ------------------------------------------------------------
add_subdirectory(dep/spdlog)


target_link_libraries(${PROJECT_NAME} PUBLIC spdlog)

# ------------------------------------------------------------
# Add glad
# ------------------------------------------------------------
add_subdirectory(dep/glad)


target_link_libraries(${PROJECT_NAME} PUBLIC glad)

# ------------------------------------------------------------
# Organize dependencies in folder
# ------------------------------------------------------------
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set_target_properties(spdlog PROPERTIES FOLDER dep)
set_target_properties(glad PROPERTIES FOLDER dep)
