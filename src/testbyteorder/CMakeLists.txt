cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME testbyteorder)

add_executable(${PROJECT_NAME} testbyteorder.c)

set_default_compiler_options(${PROJECT_NAME})
