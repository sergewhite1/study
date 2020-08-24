cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME memory-model-atomic-operations)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} main.cpp)

set_default_compiler_options(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} pthread)
