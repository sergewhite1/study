#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#include "beloff_unit_test.h"

void register_get_next_word_ut();
void register_spellcheck_ut();
void register_wordstat_ut();

int main()
{
  printf("Run unit tests...\n");

  char cwd[PATH_MAX];
  if ( getcwd(cwd, PATH_MAX) != NULL)
  {
    printf("cwd=%s\n", cwd);
  }
  else
  {
    printf("getcwd failed!\n");
  }

  register_get_next_word_ut();
  register_spellcheck_ut();
  register_wordstat_ut();

  return but_run();
}