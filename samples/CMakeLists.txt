set(CMAKE_CXX_STANDARD 17)

project(sample)

add_executable(${PROJECT_NAME} test_app.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE pengine)
