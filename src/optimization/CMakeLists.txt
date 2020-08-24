cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME optimization)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} main.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${PROJECT_NAME} PUBLIC -O0 -Wall -Wextra)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/timer)
