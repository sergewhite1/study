#ifndef UT_H_
#define UT_H_

typedef int (*ut_test_case_proc_t)(const char** name);

void ut_add_test_case(ut_test_case_proc_t test_case);

int ut_run();

#define UT_START() \
  *name = __FUNCTION__; \
  int ret = 0;

#define CHECK_EQUAL_INT(actual, expected)               \
  if (! (actual == expected))                           \
  {                                                     \
    printf("CHECK_EQUAL_INT failed!\n");                \
    printf("File: %s Line: %d\n", __FILE__, __LINE__);  \
    printf("!(%s == %s)\n", #actual, #expected);        \
    printf("actual   %s == %d\n", #actual, actual);     \
    printf("expected %s == %d\n", #expected, expected); \
    ret = 1;                                            \
  }

#endif // ! defined UT_H_
