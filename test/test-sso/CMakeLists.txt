cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME test-sso)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} $<TARGET_OBJECTS:wht_string_lib>
  main.cpp
)

set_default_compiler_options(${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME}  PUBLIC WHT_STRING_TESTING)

include_directories(${PROJECT_NAME}
  ${CMAKE_SOURCE_DIR}/src/sso
)

foreach(i RANGE 1 97)
  add_test(${PROJECT_NAME}-${i} ${PROJECT_NAME} ${i})
endforeach(i)

