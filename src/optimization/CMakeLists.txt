cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME optimization)

message("project: ${PROJECT_NAME}")
message("BEFORE CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "-Wall -O0")
message("AFTER  CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} main.cpp)
