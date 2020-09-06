cmake_minimum_required(VERSION 3.10)

project(cachegrind-demo)

function(f project is_matrix_sum_by_col)

  add_executable(${project}
    main.cpp 
    matrix.cpp
    matrix.h)

  target_include_directories(${project} PRIVATE ../../timer/technosphera/)

  if (${is_matrix_sum_by_col})
   target_compile_definitions(${project} PRIVATE MATRIX_SUM_BY_COL)
  endif()

  set_default_compiler_options(${project})

endfunction()

f(test_matrix_sum_by_row FALSE)
f(test_matrix_sum_by_col TRUE )
