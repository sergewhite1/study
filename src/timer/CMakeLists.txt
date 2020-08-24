cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "timer")

add_executable(${PROJECT_NAME} main.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${PROJECT_NAME} PUBLIC -O0 -Wall -Wextra)
endif()

