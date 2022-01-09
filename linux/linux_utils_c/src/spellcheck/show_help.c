#include "show_help.h"

#include <stdio.h>

void show_help()
{
  static const char TEXT[] = "\
Run Example:\n\
spellcheck --dict-file /usr/share/dict/american-english test.txt\
";

  puts(TEXT);
}