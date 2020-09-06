cmake_minimum_required(VERSION 3.10)

project(barrier-for-n-threads)

add_executable(${PROJECT_NAME} 
  main.c
  printf_mt.c
  printf_mt.h
)

target_link_libraries(${PROJECT_NAME} pthread)

set_default_compiler_options(${PROJECT_NAME})

set(SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/desc.txt)
set(DEST_DIR ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND cmake -E copy_if_different ${SOURCE_FILE} ${DEST_DIR}
  COMMENT "Copy (if different) file ${SOURCE_FILE} to ${DEST_DIR}")
