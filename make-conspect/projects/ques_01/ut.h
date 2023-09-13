#ifndef UT_H_
#define UT_H_

typedef int (*ut_test_case_proc_t)(const char** name);

void ut_add_test_case(ut_test_case_proc_t test_case);

int ut_run();

void ut_increment_assert_count();

#define UT_RETURN_VAR ret

#define UT_BEGIN() \
  *name = __FUNCTION__; \
  int UT_RETURN_VAR = 0;

#define UT_END() return UT_RETURN_VAR

#define UT_PRINT_FILE_AND_LINE() \
  printf("File: %s Line: %d\n", __FILE__, __LINE__)

#define UT_SET_FAILED() UT_RETURN_VAR = 1

#define CHECK_EQUAL_INT(actual, expected)               \
  ut_increment_assert_count();                          \
  if (! ((actual) == (expected)))                       \
  {                                                     \
    printf("CHECK_EQUAL_INT failed!\n");                \
    UT_PRINT_FILE_AND_LINE();                           \
    printf("!(%s == %s)\n", #actual, #expected);        \
    printf("actual   %s == %d\n", #actual, actual);     \
    printf("expected %s == %d\n", #expected, expected); \
    UT_SET_FAILED();                                    \
  }

#define CHECK_TRUE(expr)                       \
  ut_increment_assert_count();                 \
  if (!(expr))                                 \
  {                                            \
    printf("CHECK_TRUE failed!\n");            \
    UT_PRINT_FILE_AND_LINE();                  \
    printf("expr=%s value=%d\n", #expr, expr); \
    UT_SET_FAILED();                           \
  }

#define CHECK_FALSE(expr)                      \
  ut_increment_assert_count();                 \
  if ((expr))                                  \
  {                                            \
    printf("CHECK_FALSE failed!\n");           \
    UT_PRINT_FILE_AND_LINE();                  \
    printf("expr=%s value=%d\n", #expr, expr); \
    UT_SET_FAILED();                           \
  }
#endif // ! defined UT_H_
