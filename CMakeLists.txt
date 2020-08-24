cmake_minimum_required(VERSION 3.10)

include(set_default_compiler_options.cmake)

project(study)

#set(CMAKE_VERBOSE_MAKEFILE TRUE)

add_subdirectory(src)

enable_testing()

add_subdirectory(test)
