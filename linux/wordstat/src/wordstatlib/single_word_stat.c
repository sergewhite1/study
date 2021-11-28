#include "single_word_stat.h"

#include <stdlib.h>
#include <string.h>

void sws_init(struct single_word_stat* sws_ptr)
{
  memset(sws_ptr, 0, sizeof(*sws_ptr));
}

void sws_release(struct single_word_stat* sws_ptr)
{
  free(sws_ptr->word);
  sws_init(sws_ptr);
}
