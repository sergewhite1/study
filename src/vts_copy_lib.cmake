function(vts_copy_lib)
  set(dest ${CMAKE_BINARY_DIR}/src/cmake-study/cmake-post-build-copy/sumlibdemo)

  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND cmake -E make_directory ${dest}
    COMMENT "Create dir: ${dest}")

  add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND cmake -E copy *.so ${dest}
    COMMENT "Copy lib file ${PROJECT_NAME} to ${dest}")
endfunction()

vts_copy_lib()
