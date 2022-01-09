set(wordstat "wordstat")

add_executable(${wordstat}
  main.c
  show_help.c)

target_include_directories(${wordstat} PRIVATE ../wordstatlib)

target_link_libraries(${wordstat} wordstatlib)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${wordstat} PUBLIC -g -Wall -Wextra)
endif()