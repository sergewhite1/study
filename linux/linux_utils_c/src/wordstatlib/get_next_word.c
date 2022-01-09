#include "get_next_word.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_next_word(const char** curr_ptr, size_t* curr_pos_ptr)
{
  if (curr_ptr == NULL || *curr_ptr == NULL)
  {
    return NULL;
  }

  while (!isalpha(**curr_ptr))
  {
    if (**curr_ptr == '\0')
    {
      return NULL;
    }
    ++(*curr_ptr);
    ++(*curr_pos_ptr);
  }

  const char* word_start_ptr = *curr_ptr;
  size_t len = 0;

  while (isalpha(**curr_ptr))
  {
    ++(*curr_ptr);
    ++(*curr_pos_ptr);
    ++len;
  }

  char* word = (char*)malloc((len + 1) * sizeof(char));

  if (word == NULL)
  {
    printf("get_next_word: malloc error!\n");
    exit(1);
    return NULL;
  }

  memcpy(word, word_start_ptr, len);
  word[len] = '\0';

  return word;
}