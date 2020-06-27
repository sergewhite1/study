cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME pthread-demo)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} pthread)
