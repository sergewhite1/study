#include "ques.h"

#include <float.h>
#include <math.h>
#include <stdio.h>

int ques_same_value(double x1, double x2)
{
  if (fabs(x1 - x2) <= DBL_EPSILON)
  {
    return 1;
  }

  return 0;
}

ques_d_state_t ques_solve(double a,
                          double b,
                          double c,
                          double* d_ptr,
                          double* x1_ptr,
                          double* x2_ptr)
{
  *d_ptr = b * b - 4 * a * c;

  if (*d_ptr < 0)
  {
    *x1_ptr = *x2_ptr = 0.0;
    return QUES_DS_LESS_ZERO;
  }

  if (ques_same_value(*d_ptr, 0.0))
  {
    *x1_ptr = *x2_ptr = -b/(2 * a);
    return QUES_DS_ZERO;
  }

  // D > 0

  *x1_ptr = (-b - sqrt(*d_ptr)) / (2 * a);
  *x2_ptr = (-b + sqrt(*d_ptr)) / (2 * a);

  return QUES_DS_GTR_ZERO;
}

