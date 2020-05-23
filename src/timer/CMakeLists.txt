cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "timer")

message("Project: ${PROJECT_NAME}")

#message("CMAKE_CXX_FLAGS BEFORE= ${CMAKE_CXX_FLAGS}")
#set(CMAKE_CXX_FLAGS "-Wall -O0")
#message("CMAKE_CXX_FLAGS AFTER = ${CMAKE_CXX_FLAGS}")

set(CMAKE_VERBOSE_MAKEFILE TRUE)

add_executable(${PROJECT_NAME} main.cpp)
