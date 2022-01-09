#include "parse_cmd_line.h"

#include <string.h>

int parse_cmd_line(int argc,
                   char* argv[],
                   char** dict_filename_ptr,
                   char **filename_ptr)
{
  // Run example:
  // /spellcheck_s --dict-file /usr/share/dict/american-english file1.txt

  if (argc < 4)
  {
    return 1;
  }

  if (strcmp(argv[1], "--dict-file") != 0)
  {
    return 1;
  }

  *dict_filename_ptr = argv[2];

  *filename_ptr = argv[3];

  return 0;
}
