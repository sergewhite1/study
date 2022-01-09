set(wordstatlib "wordstatlib")

add_library(${wordstatlib} STATIC
  get_next_word.c
  get_next_word.h
  single_word_stat.c
  single_word_stat.h
  word_stat.c
  word_stat.h
  ws_dict.c
  ws_dict.h
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${wordstatlib} PUBLIC -g -Wall -Wextra)
endif()

target_include_directories(${wordstatlib} INTERFACE .)