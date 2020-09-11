cmake_minimum_required(VERSION 3.10)

project(std-atomic-bool)

add_executable(${PROJECT_NAME} main.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${PROJECT_NAME} PUBLIC -O3 -Wall -Wextra)
endif()
