cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "cachegrind-demo")

set(CMAKE_VERBOSE_MAKEFILE TRUE)

function(f project is_matrix_sum_by_col)

  add_executable(${project}
    main.cpp 
    matrix.cpp
    matrix.h)

  target_include_directories(${project} PRIVATE ../../timer/technosphera/)

  if (${is_matrix_sum_by_col})
   target_compile_definitions(${project} PRIVATE MATRIX_SUM_BY_COL)
  endif()

endfunction()

f(test_matrix_sum_by_row FALSE)
f(test_matrix_sum_by_col TRUE )
