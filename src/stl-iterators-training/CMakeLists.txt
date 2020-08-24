cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME stl-iterators-training)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
  binder_demo.cpp
  binder_demo.h
  person.cpp
  person.h
  main.cpp
)

set_default_compiler_options(${PROJECT_NAME})
