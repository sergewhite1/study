#ifndef WORD_STAT_H
#define WORD_STAT_H

#include <stddef.h>
#include "single_word_stat.h"

struct word_stat
{
  struct single_word_stat** data;
  size_t size;
  size_t capacity;
};

void ws_init(struct word_stat*);
void ws_sort_by_single_word_stat_count(struct word_stat*);
void ws_print(const struct word_stat*);
void ws_release(struct word_stat*);
void ws_add_word(struct word_stat*, const char*);
void ws_add_line(struct word_stat*, const char*);

#endif  // ! WORD_STAT_H