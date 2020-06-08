cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME optimization)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

message("project: ${PROJECT_NAME}")
message("BEFORE CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "-Wall -O0")
message("AFTER  CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/timer)
