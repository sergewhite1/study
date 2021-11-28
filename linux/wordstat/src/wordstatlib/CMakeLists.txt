set(wordstatlib "wordstatlib")

add_library(${wordstatlib} STATIC
  single_word_stat.c
  word_stat.c
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${wordstatlib} PUBLIC -g -Wall -Wextra)
endif()
