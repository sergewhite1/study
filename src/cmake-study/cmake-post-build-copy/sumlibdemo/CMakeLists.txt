cmake_minimum_required(VERSION 3.10)

project(sumlibdemo)

add_executable(${PROJECT_NAME} main.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${PROJECT_NAME} PUBLIC -g -Wall -Wextra)
endif()

# target_link_libraries(${PROJECT_NAME} dl sumlib)
target_link_libraries(${PROJECT_NAME} dl)
