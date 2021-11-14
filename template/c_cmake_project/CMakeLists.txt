cmake_minimum_required(VERSION 3.10)

project("hello-project")

set(CMAKE_VERBOSE_MAKEFILE TRUE)

add_executable(${PROJECT_NAME} main.c)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${PROJECT_NAME} PUBLIC -g -Wall -Wextra)
endif()

