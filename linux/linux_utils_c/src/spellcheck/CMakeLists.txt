set(spellcheck "spellcheck")

configure_file(test.txt
               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test.txt
               COPYONLY
)

add_executable(${spellcheck}
  main.c
  parse_cmd_line.c
  show_help.c
)

target_include_directories(${spellcheck} PRIVATE ..)

target_link_libraries(${spellcheck} wordstatlib)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${spellcheck} PUBLIC -g -Wall -Wextra)
endif()