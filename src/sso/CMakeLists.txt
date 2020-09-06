cmake_minimum_required(VERSION 3.10)

project (sso)

add_library(wht_string_lib OBJECT 
  wht_string.cpp
  wht_string.h
)

add_executable(${PROJECT_NAME} $<TARGET_OBJECTS:wht_string_lib>
  main.cpp
)

set_default_compiler_options(${PROJECT_NAME})

#target_link_libraries(${PROJECT_NAME} wht_string_lib)
