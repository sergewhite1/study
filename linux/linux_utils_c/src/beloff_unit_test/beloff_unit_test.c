#include "beloff_unit_test.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_CAPACITY 1024

static size_t test_count_ = 0;
static but_test_proc_t unit_tests_[TEST_CAPACITY];

int but_run()
{
  const char* filename = NULL;
  const char* curr_filename = NULL;
  const char* testname = NULL;
  int ret = 0;
  int err_code;
  size_t total_count = 0;
  size_t success_count = 0;
  size_t failed_count = 0;

  for (size_t i = 0; i < test_count_; ++i)
  {
    err_code = unit_tests_[i](&filename, &testname);
    if (curr_filename == NULL || strcmp(filename, curr_filename) != 0)
    {
      printf("Run Unit Tests from %s...\n", filename);
      curr_filename = filename;
    }

    printf("[%2ld/%2ld] %-48s %s\e[0m\n",
           i+1, test_count_, testname,
           err_code ? "\e[31mfailed" : "\e[32msuccess");

    if (err_code)
    {
      failed_count++;
      ret = 1;
    }
    else
    {
      success_count++;
    }

    total_count++;
  }

  printf("================================================================\n");
  printf("Total test count: %ld success: %ld failed: %ld\n",
         total_count,
         success_count,
         failed_count);

  return ret;
}

void but_add_test(but_test_proc_t test_proc)
{
  if (test_count_ < TEST_CAPACITY)
  {
    unit_tests_[test_count_++] = test_proc;
  }
  else
  {
    printf("but_add_test error. Test count already equals to "
           "TEST_CAPACITY=%d\n"
           "Change TEST_CAPACITY.\n", TEST_CAPACITY);
    exit(1);
  }
}