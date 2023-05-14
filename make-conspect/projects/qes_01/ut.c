#include "ut.h"

#include <stdio.h>
#include <stdlib.h>

static ut_test_case_proc_t* test_cases = NULL;

static int total_count = 0;
static int capacity    = 0;

static int assert_count = 0;

static void ut_release()
{
  if (test_cases != NULL)
  {
    free(test_cases);

    test_cases  = NULL;
    total_count = 0;
    capacity    = 0;
  }
}

void ut_add_test_case(ut_test_case_proc_t test_case)
{
  if ((total_count + 1) > capacity)
  {
    int new_capacity = capacity + 10;

    ut_test_case_proc_t* ptr =  (ut_test_case_proc_t*)
    malloc(new_capacity * sizeof(ut_test_case_proc_t*));

    free(test_cases);
    test_cases = ptr;
    capacity = new_capacity;
  }
  
  test_cases[total_count++] = test_case; 
}

int ut_run()
{
  int ret = 0;

  int success_count = 0;
  int failed_count  = 0;

  static const char* COLOR_RED     = "\033[31m";
  static const char* COLOR_GREEN   = "\033[32m";
  static const char* STOP_ESC_CODE = "\033[m";

  for (int i = 0; i < total_count; i++)
  {
    const char* test_case_name = NULL;

    int err_code = test_cases[i](&test_case_name);

    printf("%-50s ", test_case_name);

    if (err_code == 0)
    {
      printf("%sSUCCESS%s\n", COLOR_GREEN, STOP_ESC_CODE);
      success_count++;
    }
    else
    {
      printf("%sFAILED%s\n", COLOR_RED, STOP_ESC_CODE);
      failed_count++;
      ret = 1;
    }
  } 

  printf("ASSERT COUNT: %d\n", assert_count);

  printf("TEST CASES   TOTAL: %d   SUCCESS: %d   FAILED: %d\n", 
         total_count, 
         success_count, 
         failed_count);

  if (ret == 0)
  {
    printf("%sSUCCESS%s\n", COLOR_GREEN, STOP_ESC_CODE);
  }
  else
  {
    printf("%sFAILED!%s\n", COLOR_RED, STOP_ESC_CODE);
  }

  ut_release();

  return ret;
}

void ut_increment_assert_count()
{
  assert_count++;
}
