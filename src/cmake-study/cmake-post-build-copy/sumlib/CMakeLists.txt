cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME sumlib)

project(${PROJECT_NAME})

add_library(${PROJECT_NAME} SHARED
  include/sumlib.h
  sumlib.cpp
)

set_default_compiler_options(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC include)

include(${CMAKE_HOME_DIRECTORY}/src/vts_copy_lib.cmake)
