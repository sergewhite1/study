#include "word_stat.h"

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "get_next_word.h"

static void ws_add_new_word(struct word_stat* ws_ptr, const char* word)
{
  int curr_idx = ws_ptr->size;

  if (ws_ptr->size == ws_ptr->capacity)
  {
    size_t new_capacity = 2;

    if (ws_ptr->capacity)
    {
     new_capacity = 2 * ws_ptr->capacity;
    }

    ws_ptr->data = (struct single_word_stat**)
    realloc(ws_ptr->data,
    new_capacity * sizeof(struct single_word_stat*));

    if (ws_ptr->data == NULL)
    {
      printf("%s: realloc failed\n", __func__);
      return;
    }

    ws_ptr->capacity = new_capacity;

    memset(&ws_ptr->data[ws_ptr->size], 0,
           (new_capacity - ws_ptr->size) *
           sizeof(struct single_word_stat*));
  }

  ws_ptr->data[curr_idx] = (struct single_word_stat*)
                           malloc(sizeof(struct single_word_stat));

  if (ws_ptr->data[curr_idx] == NULL)
  {
    printf("%s: malloc failed!\n", __func__);
    return;
  }

  struct single_word_stat* p = ws_ptr->data[curr_idx];

  size_t len = strlen(word);
  p->word = (char*)malloc((len + 1) * sizeof(char));
  strncpy(p->word, word, len + 1);
  p->count = 1;

  ws_ptr->size++;
}

static int sort_by_count(const void* arg1, const void* arg2)
{
  const struct single_word_stat** sws1 =
  (const struct single_word_stat**)arg1;

  const struct single_word_stat** sws2 =
  (const struct single_word_stat**)arg2;

  if ((**sws1).count < (**sws2).count)
  {
    return -1;
  }
  else if ((**sws1).count == (**sws2).count)
  {
    return 0;
  }

  return 1;
}

static int sort_by_name(const void* arg1, const void* arg2)
{
  const struct single_word_stat** sws1 =
  (const struct single_word_stat**)arg1;

  const struct single_word_stat** sws2 =
  (const struct single_word_stat**)arg2;

  return strcmp((**sws1).word, (**sws2).word);
}

void ws_init(struct word_stat* ws_ptr)
{
  memset(ws_ptr, 0, sizeof(*ws_ptr));
}

void ws_sort_by_single_word_stat_count(struct word_stat* ws_ptr)
{
  qsort(ws_ptr->data,
        ws_ptr->size,
        sizeof(struct single_word_stat*),
        sort_by_count);

  size_t curr_count = 0;
  size_t begin_idx = 0;
  size_t elem_count = 0;

  for (size_t i = 0; i < ws_ptr->size; ++i)
  {
    if (curr_count == ws_ptr->data[i]->count)
    {
      elem_count++;
    }
    else if (curr_count != ws_ptr->data[i]->count)
    {
      if (elem_count > 1)
      {
        qsort(&ws_ptr->data[begin_idx],
              elem_count,
              sizeof(struct single_word_stat*),
              sort_by_name
        );
      }
      curr_count = ws_ptr->data[i]->count;
      begin_idx = i;
      elem_count = 1;
    }
  }

    // sort of the last possible chunk
    if (elem_count > 1)
    {
        qsort(&ws_ptr->data[begin_idx],
              elem_count,
              sizeof(struct single_word_stat*),
              sort_by_name
        );
    }

}

void ws_print(const struct word_stat* ws_ptr)
{
 for (size_t i = 0; i < ws_ptr->size; ++i)
 {
   printf("%ld   %s\n", ws_ptr->data[i]->count, ws_ptr->data[i]->word);
 }
}

void ws_release(struct word_stat* ws_ptr)
{
  for (size_t i = 0; i < ws_ptr->size; ++i)
  {
    sws_release(ws_ptr->data[i]);
    free(ws_ptr->data[i]);
  }
  free(ws_ptr->data);

  ws_init(ws_ptr);
}

void ws_add_word(struct word_stat* ws_ptr, const char* word)
{
  for (size_t i = 0; i < ws_ptr->size; ++i)
  {
    if (strcmp(ws_ptr->data[i]->word, word) == 0)
    {
      ws_ptr->data[i]->count++;
      return;
    }
  }

  ws_add_new_word(ws_ptr, word);
}

void ws_add_line(struct word_stat* ws_ptr, const char* line)
{
  if (line == NULL)
  {
    return;
  }

  const char* curr_ptr = line;
  size_t curr_pos = 0;

  char* word = NULL;

  while ((word = get_next_word(&curr_ptr, &curr_pos)) != NULL)
  {
    ws_add_word(ws_ptr, word);
    free(word);
  }
}