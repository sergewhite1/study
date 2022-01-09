#include "ws_dict.h"

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int ws_dict_add_word(ws_dict* ws_dict_ptr, const char* word)
{
  int curr_idx = ws_dict_ptr->size;

  if (ws_dict_ptr->size == ws_dict_ptr->capacity)
  {
    size_t new_capacity = 2;

    if (ws_dict_ptr->capacity)
    {
     new_capacity = 2 * ws_dict_ptr->capacity;
    }

    ws_dict_ptr->data = (char**)
    realloc(ws_dict_ptr->data, new_capacity * sizeof(char*));

    if (ws_dict_ptr->data == NULL)
    {
      printf("%s: realloc failed\n", __func__);
      return 1;
    }

    ws_dict_ptr->capacity = new_capacity;

    memset(&ws_dict_ptr->data[ws_dict_ptr->size], 0,
           (new_capacity - ws_dict_ptr->size) *
           sizeof(char*));
  }

  size_t word_len = strlen(word);
  char* buffer = (char*)malloc((word_len + 1) * sizeof(char));
  strncpy(buffer, word, word_len + 1);
  ws_dict_ptr->data[curr_idx] = buffer;

  ws_dict_ptr->size++;

  return 0;
}

static int bserach_comp_func(const void *arg1, const void* arg2)
{
  return strcmp(*((const char**)arg1), *((const char**)arg2));
}

void ws_dict_check_word_(const ws_dict* ws_dict_ptr,
                        const char* word,
                        size_t line_num,
                        size_t pos)
{
  void *p = bsearch(&word,
                    ws_dict_ptr->data,
                    ws_dict_ptr->size,
                    sizeof(char*),
                    bserach_comp_func);
  if (p == NULL)
  {
    printf("Line: %ld pos: %ld not found: \"%s\"\n",
           line_num,
           pos,
           word);
  }
}

int ws_dict_check_word(const ws_dict* ws_dict_ptr,
                       const char* word)
{
  if (word == NULL || *word == '\0')
  {
    return 1;
  }

  void *p = bsearch(&word,
                    ws_dict_ptr->data,
                    ws_dict_ptr->size,
                    sizeof(char*),
                    bserach_comp_func);

  if (p != NULL)
  {
    return 1;
  }

  size_t len = strlen(word);
  char* word_lower_case = (char*) malloc((len+1) * sizeof(char));
  if (word_lower_case == NULL)
  {
    printf("ws_dict_check_word malloc failed!\n");
    exit(1);
    return 0;
  }

  for (size_t i = 0; i < len; ++i)
  {
    word_lower_case[i] = tolower(word[i]);
  }
  word_lower_case[len] = '\0';

  p = bsearch(&word_lower_case,
              ws_dict_ptr->data,
              ws_dict_ptr->size,
              sizeof(char*),
              bserach_comp_func);

  free(word_lower_case);

  return p == NULL ? 0 : 1;
}

void ws_dict_init(ws_dict* ws_dict_ptr)
{
  memset(ws_dict_ptr, 0, sizeof(*ws_dict_ptr));
}

void ws_dict_release(ws_dict* ws_dict_ptr)
{
  for (size_t i = 0; i < ws_dict_ptr->size; ++i)
  {
    free(ws_dict_ptr->data[i]);
  }

  free(ws_dict_ptr->data);

  ws_dict_init(ws_dict_ptr);
}

int ws_dict_load_from_file(ws_dict* ws_dict_ptr, const char* filename)
{
  FILE* f = fopen(filename, "r");

  if (f == NULL)
  {
    return 1;
  }

  char* line = NULL;
  size_t len = 0;

  ssize_t nread;
  int err_code;
  int ret = 0;

  while ((nread = getline(&line, &len, f)) != -1)
  {
    if (nread <= 1)
    {
      continue;
    }

    if (line[nread-1] == '\n')
    {
      line[nread-1] = '\0';
    }
    else
    {
      char* tmp = line;
      line = (char*) malloc((nread+1) * sizeof(char));
      if (line == NULL)
      {
        printf("ws_dict_load_from_file malloc failed!\n");
        exit(1);
      }

      memcpy(line, tmp, nread);
      line[nread] = '\0';
      free(tmp);
    }

    err_code = ws_dict_add_word(ws_dict_ptr, line);
    if (err_code)
    {
      printf("Error of add word \"%s\" to dictionary.\n", line);
      ret = 1;
      break;
    }
  }

  free(line);
  fclose(f);

  qsort(ws_dict_ptr->data,
        ws_dict_ptr->size,
        sizeof(char*),
        bserach_comp_func);

  return ret;
}
