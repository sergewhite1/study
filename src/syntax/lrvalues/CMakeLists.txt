cmake_minimum_required(VERSION 3.10)

project(lrvalues)

add_executable(${PROJECT_NAME}
  a.cpp
  a.h
  functions.cpp
  functions.h
  main.cpp
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${PROJECT_NAME} PUBLIC -O0 -Wall -Wextra)
endif()
