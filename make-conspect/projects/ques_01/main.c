#include <stdio.h>
#include <stdlib.h>

#include "ques.h"

static int get_input_d(const char* str, double* p)
{
  printf("%s", str);

  int ret = scanf("%lf", p);

  if (ret != 1)
  {
    printf("Error of parsing %s\n", str);
    exit(1);
  }

  return ret;
}


int main()
{
  printf("Quadric Equation Solver\n");
  
  double a, b, c, D, x1, x2;

  a = b = c = D = x1 = x2 = 0.0;

  get_input_d("a=", &a);
  get_input_d("b=", &b);
  get_input_d("c=", &c);

  qes_d_state_t ds = qes_solve(a, b, c, &D, &x1, &x2);

  switch(ds)
  {
    case QES_DS_LESS_ZERO:
      printf("D=%lf < 0 - no roots in real domain.\n", D);
      break;

    case QES_DS_ZERO:
      printf("D=0\n");
      printf("x1=x2=%lf\n", x1);
      break;

    case QES_DS_GTR_ZERO:
      printf("D=%lf\n", D);
      printf("x1=%lf\n", x1);
      printf("x2=%lf\n", x2);
      break;

    default:
      printf("Unexpected discriminant state ds=%d\n", ds);
      exit(1);
  }

  return 0;
}

