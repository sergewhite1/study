#include <stdio.h>
#include <stdlib.h>

#include "parse_cmd_line.h"
#include "show_help.h"
#include "wordstatlib/get_next_word.h"
#include "wordstatlib/ws_dict.h"

#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
  printf("spellcheck...\n");

  char* dict_filename = NULL;
  char* filename = NULL;

  int err_code = parse_cmd_line(argc, argv, &dict_filename, &filename);

  if (err_code)
  {
    printf("Error of parse command line.\n");
    show_help();
    return 1;
  }

  ws_dict dict;
  ws_dict_init(&dict);

  FILE* stream = NULL;

  char* line      = NULL;
  size_t line_len = 0;

  size_t curr_line_num = 1;

  const char* curr_ptr  = NULL;
  size_t curr_pos = 0;

  int ret = 0;

  do
  {
    err_code = ws_dict_load_from_file(&dict, dict_filename);
    if (err_code)
    {
     printf("Error load dict from file: %s\n", dict_filename);
     ret = 1;
     break;
    }

    printf("Dict loaded success.\n");

    stream = fopen(filename, "r");

    if (stream == NULL)
    {
      printf("Error open file: %s\n", filename);
      ret = 1;
      break;
    }

    ssize_t nread = 0;

    while ((nread = getline(&line, &line_len, stream)) != -1)
    {
      curr_ptr = line;
      while (curr_ptr != NULL)
      {
        char* word = get_next_word(&curr_ptr, &curr_pos);
        if (word == NULL)
        {
          break;
        }

        int res = ws_dict_check_word(&dict, word);

        if (res == 0)
        {
          size_t p = curr_pos - strlen(word);
          printf("Line: %ld Pos: %ld: word not found: \"%s\"\n",
          curr_line_num,
          p,
          word);
        }

        free(word);
      }
      //ws_dict_check_line(&dict, line, curr_line_num);
      ++curr_line_num;
    }

  } while (0);

  free(line);
  ws_dict_release(&dict);

  if (stream != NULL)
  {
    fclose(stream);
  }

  return ret;
}