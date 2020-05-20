cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "memory-model-basic")

message("${PROJECT_NAME} CMAKE_CXX_FLAGS BEFORE: ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "-Wall -g")
message("${PROJECT_NAME} CMAKE_CXX_FLAGS AFTER : ${CMAKE_CXX_FLAGS}")

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} pthread)
