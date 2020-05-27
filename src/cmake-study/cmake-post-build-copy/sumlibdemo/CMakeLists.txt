cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME sumlibdemo)

set(CMAKE_CXX_FLAGS "-Wall -g")

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} main.cpp)

# target_link_libraries(${PROJECT_NAME} dl sumlib)
target_link_libraries(${PROJECT_NAME} dl)
