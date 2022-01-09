#include <stdio.h>
#include <stdlib.h>

#include "beloff_unit_test.h"
#include "ws_dict.h"

static ws_dict dict;

static int ws_dict_load_from_file_test(const char** filename,
                                       const char** testname)
{
  *filename = BUT_FILENAME;
  *testname = BUT_FUNCTION;

  static const char* DICT_FILENAME = "sample_dict.txt";

  int ret = 0;

  int res =  ws_dict_load_from_file(&dict, DICT_FILENAME);

  if (res != 0)
  {
    printf("Error of loading dict: %s\n", DICT_FILENAME);
    ret = 1;
  }

  return ret;
}

static int ws_dict_release_test(const char** filename,
                                const char** testname)
{
  *filename = BUT_FILENAME;
  *testname = BUT_FUNCTION;

  ws_dict_release(&dict);

  int ret = 0;

  if (dict.size)
  {
    ret = 1;
  }

  return ret;
}

static int ws_dict_smoke_test(const char** filename,
                              const char** testname)
{
  *filename = BUT_FILENAME;
  *testname = BUT_FUNCTION;

  if (dict.size == 0)
  {
    return 1;
  }

  int ret = 0;

  int res =  ws_dict_check_word(&dict, "hello");

  if (!res)
  {
    ret = 1;
  }

  return ret;
}

static int ws_dict_uppercase_test(const char** filename,
                                  const char** testname)
{
  *filename = BUT_FILENAME;
  *testname = BUT_FUNCTION;

  if (dict.size == 0)
  {
    return 1;
  }

  int ret = 0;
  int res = ws_dict_check_word(&dict, "Her");

  if (res == 0)
  {
    ret = 1;
  }

  return ret;
}


static int ws_dict_null_test(const char** filename,
                             const char** testname)
{
  *filename = BUT_FILENAME;
  *testname = BUT_FUNCTION;

  if (dict.size == 0)
  {
    return 1;
  }

  int ret = 0;

  int res = ws_dict_check_word(&dict, NULL);

  if (res == 0)
  {
    ret = 1;
  }

  return ret;
}


static int ws_dict_empty_str_test(const char** filename,
                                  const char** testname)
{
  *filename = BUT_FILENAME;
  *testname = BUT_FUNCTION;

  if (dict.size == 0)
  {
    return 1;
  }

  int ret = 0;

  int res = ws_dict_check_word(&dict, "");

  if (res == 0)
  {
    ret = 1;
  }

  return ret;
}

void register_spellcheck_ut()
{
  ws_dict_init(&dict);

  but_add_test(ws_dict_load_from_file_test);

  but_add_test(ws_dict_smoke_test);
  but_add_test(ws_dict_uppercase_test);
  but_add_test(ws_dict_null_test);
  but_add_test(ws_dict_empty_str_test);

  but_add_test(ws_dict_release_test);
}