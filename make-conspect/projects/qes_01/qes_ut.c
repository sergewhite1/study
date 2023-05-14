#include <math.h>
#include <stdio.h>

#include "ut.h"
#include "qes.h"

#define CHECK_QES_SAME_VALUE(actual, expected)                \
  ut_increment_assert_count();                                \
  if (!qes_same_value((actual), (expected)))                  \
  {                                                           \
    printf("CHECK_QES_SAME_VALUE failed!\n");                 \
    UT_PRINT_FILE_AND_LINE();                                 \
    printf("!(qes_same_value(%s, %s)\n", #actual, #expected); \
    printf("actual   %s == %lf\n", #actual, actual);          \
    printf("expected %s == %lf\n", #expected, expected);      \
    UT_SET_FAILED();                                          \
   }

#define CHECK_NOT_QES_SAME_VALUE(actual, expected)            \
  ut_increment_assert_count();                                \
  if (qes_same_value((actual), (expected)))                   \
  {                                                           \
    printf("CHECK_NOT_QES_SAME_VALUE failed!\n");             \
    UT_PRINT_FILE_AND_LINE();                                 \
    printf("qes_same_value(%s, %s)\n", #actual, #expected);   \
    printf("actual   %s == %lf\n", #actual, actual);          \
    printf("expected %s == %lf\n", #expected, expected);      \
    UT_SET_FAILED();                                          \
   }

static int test_qes_same_value_smoke(const char** name)
{
  UT_BEGIN();

  double a  = 1.0;
  double pi = 2 * asin(1.0);
  double b  = sin(pi/2.0);
  
  CHECK_QES_SAME_VALUE(a, b);

  UT_END();
}

static int test_qes_same_value_negative(const char** name)
{

  UT_BEGIN();

  double a = 1.0;
  double b = 2.0;

  CHECK_NOT_QES_SAME_VALUE(a, b);

  UT_END();
}

static int test_qes_solve_discriminant_less_zero(const char** name)
{
  UT_BEGIN();

  double D  = 0.0;
  double x1 = 0.0;
  double x2 = 0.0;

  CHECK_EQUAL_INT(qes_solve(0.5, 2.5, 3.5, &D, &x1, &x2), QES_DS_LESS_ZERO);
  CHECK_QES_SAME_VALUE(D, -0.75);

  UT_END();
}

static int test_qes_solve_discriminant_zero(const char** name)
{
  UT_BEGIN();

  double D  = 0.0;
  double x1 = 0.0;
  double x2 = 0.0;

  CHECK_EQUAL_INT(qes_solve(1, 4, 4, &D, &x1, &x2), QES_DS_ZERO);
  CHECK_QES_SAME_VALUE(D, 0.0);
  CHECK_QES_SAME_VALUE(x1, -2.0);
  CHECK_QES_SAME_VALUE(x2, -2.0);

  UT_END();
}

static int test_qes_solve_discriminant_grt_zero(const char** name)
{
  UT_BEGIN();

  double D  = 0.0;
  double x1 = 0.0;
  double x2 = 0.0;

  CHECK_EQUAL_INT(qes_solve(1, 10, -24, &D, &x1, &x2), QES_DS_GTR_ZERO);
  CHECK_QES_SAME_VALUE(D, 196.0);
  CHECK_QES_SAME_VALUE(x1, -12.0);
  CHECK_QES_SAME_VALUE(x2, 2.0);

  UT_END();
}

int main()
{
  printf("Run qes_ut\n");

  ut_add_test_case(test_qes_same_value_smoke);
  ut_add_test_case(test_qes_same_value_negative);
  ut_add_test_case(test_qes_solve_discriminant_less_zero);
  ut_add_test_case(test_qes_solve_discriminant_zero);
  ut_add_test_case(test_qes_solve_discriminant_grt_zero);

  return ut_run();
}
