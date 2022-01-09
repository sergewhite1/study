#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "show_help.h"
#include "single_word_stat.h"
#include "word_stat.h"

static void process_file(const char* filename, struct word_stat* ws_ptr)
{
  FILE* f = fopen(filename, "r");

  if (f == NULL )
  {
    printf("Error opening file: %s\n", filename);
    return;
  }

  size_t len = 0;
  ssize_t nread = 0;
  char* line = NULL;

  while ((nread = getline(&line, &len, f)) != -1)
  {
    ws_add_line(ws_ptr, line);
  }

  free(line);
  fclose(f);
}

int main(int argc, char* argv[])
{
  if (argc <= 1)
  {
    printf("Error! No filename!\n");
    show_help();
    return 1;
  }

  struct word_stat ws;
  ws_init(&ws);

  for (int arg_index = 1; arg_index < argc; ++arg_index)
  {
    char* filename = argv[arg_index];
    process_file(filename, &ws);
  }

  ws_sort_by_single_word_stat_count(&ws);

  ws_print(&ws);

  ws_release(&ws);

  return 0;
}