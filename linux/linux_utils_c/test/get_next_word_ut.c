#include <stdio.h>
#include <stdlib.h>

#include "beloff_unit_test.h"
#include "get_next_word.h"

int get_next_word_smoke(const char** filename, const char** testname)
{
  *filename = BUT_FILENAME;
  *testname = BUT_FUNCTION;

  const char* LINE = "   Hello, World!   ";

  const char* curr_ptr = LINE;
  size_t curr_pos = 0;
  char* word = NULL;

  int ret = 0;

  do
  {
    word = get_next_word(&curr_ptr, &curr_pos);
    if (!(word && strcmp(word, "Hello") == 0 && curr_pos == 8))
    {
      ret = 1;
      break;
    }
    free(word); word = NULL;

    word = get_next_word(&curr_ptr, &curr_pos);
    if (!(word && strcmp(word, "World") == 0 && curr_pos == 15))
    {
      ret = 1;
      break;
    }
    free(word); word = NULL;

    word = get_next_word(&curr_ptr, &curr_pos);
    if (word != NULL)
    {
      ret = 1;
      break;
    }

  } while(0);

  free(word);
  return ret;
}

void register_get_next_word_ut()
{
  but_add_test(get_next_word_smoke);
}