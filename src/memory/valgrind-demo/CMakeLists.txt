cmake_minimum_required(VERSION 3.10)

project(valgrind-demo)

add_executable(${PROJECT_NAME} main.c)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${PROJECT_NAME} PUBLIC -g -O0 -Wall -Wextra)
endif()
