cmake_minimum_required(VERSION 3.10)

project(study)

message(STATUS "main file: before update: CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")

if(UNIX)
	set(CMAKE_CXX_FLAGS "-Wall")
endif(UNIX)

message(STATUS "main file: after  update: CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")

add_subdirectory(src)

enable_testing()

add_subdirectory(test)
