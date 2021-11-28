#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "single_word_stat.h"
#include "word_stat.h"

typedef int (*test_proc_t)(const char** test_name);

int sws_init_test(const char** test_name)
{
  *test_name = __func__;

  struct single_word_stat sws_obj;
  sws_obj.count = 111;
  sws_obj.word = "hello!";

  sws_init(&sws_obj);

  if ((sws_obj.count == 0) && (sws_obj.word == NULL))
  {
    return 0;
  }

  return 1;
}

int sws_release_test(const char** test_name)
{
  *test_name = __func__;

  struct single_word_stat sws_obj;

  sws_init(&sws_obj);

  const char* str = "hello";
  size_t len = strlen(str);
  sws_obj.word = (char*) malloc((len + 1) * sizeof(char));
  strncpy(sws_obj.word, str, (len + 1) * sizeof(char));

  sws_obj.count = 1;

  sws_release(&sws_obj);

  if ((sws_obj.count == 0) && (sws_obj.word == NULL))
  {
    return 0;
  }

  return 1;
}

int ws_init_test(const char** test_name)
{
  *test_name = __func__;

  struct word_stat ws_obj;
  ws_obj.data = (struct single_word_stat**)0xff;
  ws_obj.size = 12;
  ws_obj.capacity = 33;

  ws_init(&ws_obj);

  if ((ws_obj.data == NULL) &&
      (ws_obj.size == 0) &&
      (ws_obj.capacity == 0))
  {
    return 0;
  }

  return 1;
}

int ws_add_word_test(const char** test_name)
{
  *test_name = __func__;

  struct word_stat ws;

  ws_init(&ws);

  ws_add_word(&ws, "hello");
  ws_add_word(&ws, "World");
  ws_add_word(&ws, "hello");
  ws_add_word(&ws, "dev");

  int ret = 0;

  do
  {
    if (ws.size != 3)
    {
      ret = 1;
      break;
    }

    if ((strcmp(ws.data[0]->word, "hello") != 0) || ws.data[0]->count != 2)
    {
      ret = 1;
      break;
    }

    if ((strcmp(ws.data[1]->word, "World") != 0) || ws.data[1]->count != 1)
    {
      ret = 1;
      break;
    }

    if ((strcmp(ws.data[2]->word, "dev") != 0) || ws.data[2]->count != 1)
    {
      ret = 1;
      break;
    }
  } while (0);

  ws_release(&ws);

  return ret;
}

int ws_sort_by_single_word_stat_count_test(const char** test_name)
{
  *test_name = __func__;

  /* Input data: "zzz hello World hello dev zzz"
   * Expected result:
   * 1 World
   * 1 dev
   * 2 hello
   * 2 zzz
   */

  struct word_stat ws;

  ws_init(&ws);

  ws_add_word(&ws, "zzz");
  ws_add_word(&ws, "hello");
  ws_add_word(&ws, "World");
  ws_add_word(&ws, "hello");
  ws_add_word(&ws, "dev");
  ws_add_word(&ws, "zzz");

  ws_sort_by_single_word_stat_count(&ws);

  //ws_print(&ws);

  int ret = 0;

  do
  {
    if (ws.size != 4)
    {
      ret = 1;
      break;
    }

    if ((strcmp(ws.data[0]->word, "World") != 0) || (ws.data[0]->count != 1) ||
        (strcmp(ws.data[1]->word, "dev"  ) != 0) || (ws.data[1]->count != 1) ||
        (strcmp(ws.data[2]->word, "hello") != 0) || (ws.data[2]->count != 2) ||
        (strcmp(ws.data[3]->word, "zzz")   != 0) || (ws.data[3]->count != 2))
    {
      ret = 1;
    }
  } while (0);

  ws_release(&ws);

  // for valgrind test
  ws_sort_by_single_word_stat_count(&ws);

  return ret;
}

int ws_add_line_test(const char** test_name)
{
  *test_name = __func__;

  struct word_stat ws;

  ws_init(&ws);

  // Add empty line
  ws_add_line(&ws, NULL);

  ws_add_line(&ws, "\n");

  ws_add_line(&ws, "Test file.");
  ws_add_line(&ws, "Line 2;");
  ws_add_line(&ws, "hello verylongword one and the last word");

/* Expected result:
 * 1 Line
 * 1 Test
 * 1 and
 * 1 file
 * 1 hello
 * 1 last
 * 1 one
 * 1 the
 * 1 verylongword
 * 1 word
 */

  ws_sort_by_single_word_stat_count(&ws);

  int ret = 0;

  do
  {
    if (ws.size != 10)
    {
      ret = 1;
      break;
    }

    if ((strcmp(ws.data[0]->word, "Line" ) != 0) || (ws.data[0]->count != 1) ||
        (strcmp(ws.data[1]->word, "Test" ) != 0) || (ws.data[1]->count != 1) ||
        (strcmp(ws.data[2]->word, "and"  ) != 0) || (ws.data[2]->count != 1) ||
        (strcmp(ws.data[3]->word, "file" ) != 0) || (ws.data[3]->count != 1) ||
        (strcmp(ws.data[4]->word, "hello") != 0) || (ws.data[4]->count != 1) ||
        (strcmp(ws.data[5]->word, "last" ) != 0) || (ws.data[5]->count != 1) ||
        (strcmp(ws.data[6]->word, "one"  ) != 0) || (ws.data[6]->count != 1) ||
        (strcmp(ws.data[7]->word, "the"  ) != 0) || (ws.data[7]->count != 1) ||
        (strcmp(ws.data[8]->word, "verylongword") != 0) || (ws.data[8]->count != 1) ||
        (strcmp(ws.data[9]->word, "word" ) != 0) || (ws.data[9]->count != 1))
    {
      ret = 1;
    }
  } while (0);

  //ws_print(&ws);

  ws_release(&ws);

  return ret;
}

const test_proc_t TEST_PROC[] = {
  sws_init_test
  ,sws_release_test
  ,ws_init_test
  ,ws_add_word_test
  ,ws_sort_by_single_word_stat_count_test
  ,ws_add_line_test
};

const int TEST_COUNT = sizeof(TEST_PROC) / sizeof(TEST_PROC[0]);

int main()
{
  int ret = 0;
  int success_count = 0;
  int failed_count = 0;
  for (int i = 0; i < TEST_COUNT; ++i)
  {
    const char* test_name = NULL;

    int err = TEST_PROC[i](&test_name);

    if (err == 0)
    {
      printf("Test %d of %d %-44s success\n", i + 1, TEST_COUNT, test_name);
      success_count++;
    }
    else
    {
      printf("Test %d of %d %-44s failed\n", i + 1, TEST_COUNT, test_name);
      failed_count++;
      ret = 1;
    }
  }

  printf("=======================================\n");
  printf("Total test count: %d success: %d failed: %d\n",
         TEST_COUNT, success_count, failed_count);

  return ret;
}