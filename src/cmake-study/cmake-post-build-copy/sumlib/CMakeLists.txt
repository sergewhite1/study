cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME sumlib)

project(${PROJECT_NAME})

add_library(${PROJECT_NAME} SHARED
  include/sumlib.h
  sumlib.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

add_custom_command(
  TARGET sumlib POST_BUILD
  COMMAND cmake -E copy_if_different *.so ../sumlibdemo/)