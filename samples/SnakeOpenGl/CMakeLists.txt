set(CMAKE_CXX_STANDARD 17)

project(SnakeOpenGL)

add_executable(${PROJECT_NAME} SnakeOpenGL.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE pengine)
