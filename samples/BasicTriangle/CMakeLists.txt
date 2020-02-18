set(CMAKE_CXX_STANDARD 17)

project(BasicTriangle)

add_executable(${PROJECT_NAME} BasicTriangle.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE pengine)
