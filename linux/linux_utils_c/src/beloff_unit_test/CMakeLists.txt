set(beloff_unit_test "beloff_unit_test")

add_library(${beloff_unit_test} STATIC
  beloff_unit_test.c
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${beloff_unit_test} PUBLIC -g -Wall -Wextra)
endif()

target_include_directories(${beloff_unit_test} INTERFACE .)