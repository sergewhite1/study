cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "valgrind-demo")

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} main.c)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${PROJECT_NAME} PUBLIC -g -O0 -Wall -Wextra)
endif()
