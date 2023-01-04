#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "beloff_unit_test.h"

#include "single_word_stat.h"
#include "word_stat.h"

static int sws_init_test(const char** filename, const char** testname)
{
  BUT_BEGIN

  struct single_word_stat sws_obj;
  sws_obj.count = 111;
  sws_obj.word = "hello!";

  sws_init(&sws_obj);

  CHECK_EQUAL_UL(sws_obj.count, 0UL);
  CHECK_STR_IS_NULL(sws_obj.word);

  BUT_END
}

static int sws_release_test(const char** filename, const char** testname)
{
  BUT_BEGIN

  struct single_word_stat sws_obj;

  sws_init(&sws_obj);

  const char* str = "hello";
  size_t len = strlen(str);
  sws_obj.word = (char*) malloc((len + 1) * sizeof(char));
  strncpy(sws_obj.word, str, (len + 1) * sizeof(char));

  sws_obj.count = 1;

  sws_release(&sws_obj);

  CHECK_EQUAL_UL(sws_obj.count, 0UL);
  CHECK_STR_IS_NULL(sws_obj.word);

  BUT_END
}

static int ws_init_test(const char** filename, const char** testname)
{
  BUT_BEGIN

  struct word_stat ws_obj;
  ws_obj.data = (struct single_word_stat**)0xff;
  ws_obj.size = 12;
  ws_obj.capacity = 33;

  ws_init(&ws_obj);

  CHECK_PTR_IS_NULL(ws_obj.data);
  CHECK_EQUAL_UL(ws_obj.size, 0UL);
  CHECK_EQUAL_UL(ws_obj.size, 0UL);

  BUT_END
}

static int ws_add_word_test(const char** filename, const char** testname)
{
  BUT_BEGIN

  struct word_stat ws;

  ws_init(&ws);

  ws_add_word(&ws, "hello");
  ws_add_word(&ws, "World");
  ws_add_word(&ws, "hello");
  ws_add_word(&ws, "dev");

  do
  {
    CHECK_EQUAL_UL(ws.size, 3UL);
    if (ret)
    {
      break;
    }

    CHECK_EQUAL_STR(ws.data[0]->word, "hello");
    CHECK_EQUAL_UL (ws.data[0]->count, 2UL);

    CHECK_EQUAL_STR(ws.data[1]->word, "World");
    CHECK_EQUAL_UL (ws.data[1]->count, 1UL);

    CHECK_EQUAL_STR(ws.data[2]->word, "dev");
    CHECK_EQUAL_UL (ws.data[2]->count, 1UL);

  } while (0);

  ws_release(&ws);

  BUT_END
}

static int ws_sort_by_single_word_stat_count_test(const char** filename,
                                                  const char** testname)
{
  BUT_BEGIN

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

  do
  {
    CHECK_EQUAL_UL(ws.size, 4UL);
    if (ret)
    {
      break;
    }

    CHECK_EQUAL_STR(ws.data[0]->word, "World");
    CHECK_EQUAL_UL (ws.data[0]->count, 1UL);

    CHECK_EQUAL_STR(ws.data[1]->word, "dev");
    CHECK_EQUAL_UL (ws.data[1]->count, 1UL);

    CHECK_EQUAL_STR(ws.data[2]->word, "hello");
    CHECK_EQUAL_UL (ws.data[2]->count, 2UL);

    CHECK_EQUAL_STR(ws.data[3]->word, "zzz");
    CHECK_EQUAL_UL (ws.data[3]->count, 2UL);

  } while (0);

  ws_release(&ws);

  // for valgrind test
  ws_sort_by_single_word_stat_count(&ws);

  BUT_END
}

static int ws_add_line_test(const char** filename, const char** testname)
{
  BUT_BEGIN

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

  do
  {
    CHECK_EQUAL_UL(ws.size, 10UL);
    if (ret)
    {
      break;
    }

    CHECK_EQUAL_STR(ws.data[0]->word, "Line");
    CHECK_EQUAL_UL (ws.data[0]->count, 1UL);

    CHECK_EQUAL_STR(ws.data[1]->word, "Test");
    CHECK_EQUAL_UL (ws.data[1]->count, 1UL);

    CHECK_EQUAL_STR(ws.data[2]->word, "and");
    CHECK_EQUAL_UL (ws.data[2]->count, 1UL);

    CHECK_EQUAL_STR(ws.data[3]->word, "file");
    CHECK_EQUAL_UL (ws.data[3]->count, 1UL);

    CHECK_EQUAL_STR(ws.data[4]->word, "hello");
    CHECK_EQUAL_UL (ws.data[4]->count, 1UL);

    CHECK_EQUAL_STR(ws.data[5]->word, "last");
    CHECK_EQUAL_UL (ws.data[5]->count, 1UL);

    CHECK_EQUAL_STR(ws.data[6]->word, "one");
    CHECK_EQUAL_UL (ws.data[6]->count, 1UL);

    CHECK_EQUAL_STR(ws.data[7]->word, "the");
    CHECK_EQUAL_UL (ws.data[7]->count, 1UL);

    CHECK_EQUAL_STR(ws.data[8]->word, "verylongword");
    CHECK_EQUAL_UL (ws.data[8]->count, 1UL);

    CHECK_EQUAL_STR(ws.data[9]->word, "word");
    CHECK_EQUAL_UL (ws.data[9]->count, 1UL);

  } while (0);

  //ws_print(&ws);

  ws_release(&ws);

  BUT_END
}

void register_wordstat_ut()
{
  but_add_test(sws_init_test);
  but_add_test(sws_release_test);
  but_add_test(ws_init_test);
  but_add_test(ws_add_word_test);
  but_add_test(ws_sort_by_single_word_stat_count_test);
  but_add_test(ws_add_line_test);
}