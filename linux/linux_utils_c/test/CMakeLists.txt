set(unit_tests "unit_tests")

add_executable(${unit_tests}
  get_next_word_ut.c
  main.c
  spellcheck_ut.c
  wordstat_ut.c
)

target_link_libraries(${unit_tests}
  beloff_unit_test
  wordstatlib)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${unit_tests} PUBLIC -g -Wall -Wextra)
endif()

configure_file(
  sample_dict.txt
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sample_dict.txt
  COPYONLY
)

#add_custom_command(
#  TARGET ${unit_tests} PRE_BUILD
#  COMMAND ${CMAKE_COMMAND} -E copy
#     ${CMAKE_SOURCE_DIR}/test/sample_dict.txt
#     ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sample_dict.txt)

add_custom_command(
  TARGET ${unit_tests} POST_BUILD
  COMMAND ${unit_tests}
  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
  COMMENT "Run ${unit_tests}")

#set_target_properties(
#  ${unit_tests} PROPERTIES
#  VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})