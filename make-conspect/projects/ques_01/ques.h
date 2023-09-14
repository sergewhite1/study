#ifndef QUES_H_
#define QUES_H_

typedef enum __ques_d_state_t { QUES_DS_LESS_ZERO
                               ,QUES_DS_ZERO
                               ,QUES_DS_GTR_ZERO
                              } ques_d_state_t;

/* Return Value:
 * 0 - not same value
 * 1 -     same value
 */
int ques_same_value(double x1, double x2);

ques_d_state_t ques_solve(double a,
                          double b,
                          double c,
                          double* d_ptr,
                          double* x1_ptr,
                          double* x2_ptr);

#endif // ! defined QUES_H_
