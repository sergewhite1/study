cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME pthread-demo)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} main.c utils.c utils.h)

set_default_compiler_options(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} m pthread)
