#ifndef SINGLE_WORD_STAT_H
#define SINGLE_WORD_STAT_H

#include <stddef.h>

struct single_word_stat
{
  char* word;
  size_t count;
};

void sws_init(struct single_word_stat*);
void sws_release(struct single_word_stat*);

#endif // ! SINGLE_WORD_STAT_H