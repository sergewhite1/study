cmake_minimum_required(VERSION 3.10)

project("hello-project")

#set(CMAKE_VERBOSE_MAKEFILE TRUE)

set(hello_app "hello_app")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_executable(${hello_app} main.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${hello_app} PUBLIC -g -Wall -Wextra)
endif()

