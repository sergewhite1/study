set(wordstat_ut "wordstat_ut")

add_executable(${wordstat_ut} wordstat_ut.c)

target_include_directories(${wordstat_ut} PRIVATE
  ${CMAKE_HOME_DIRECTORY}/src/wordstatlib)

target_link_libraries(${wordstat_ut} wordstatlib)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${wordstat_ut} PUBLIC -g -Wall -Wextra)
endif()

add_custom_command(TARGET ${wordstat_ut} POST_BUILD
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${wordstat_ut}
  COMMENT "Run ${wordstat_ut}")