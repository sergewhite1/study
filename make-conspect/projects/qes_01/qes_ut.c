#include <math.h>
#include <stdio.h>

#include "ut.h"
#include "qes.h"

static int test_qes_same_value_smoke(const char** name)
{
  UT_START();

  double a  = 1.0;
  double pi = 2 * asin(1.0);
  double b  = sin(pi/2.0);
  
  CHECK_EQUAL_INT(qes_same_value(a, b), 1);

  return ret;
}

static int test_qes_same_value_negative(const char** name)
{

  UT_START();

  double a = 1.0;
  double b = 2.0;

  CHECK_EQUAL_INT(qes_same_value(a, b), 0);

  return ret;
}

int main()
{
  printf("Run qes_ut\n");

  ut_add_test_case(test_qes_same_value_smoke);
  ut_add_test_case(test_qes_same_value_negative);

  return ut_run();
}
