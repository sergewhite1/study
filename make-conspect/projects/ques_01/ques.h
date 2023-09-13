#ifndef QES_H_
#define QES_H_

typedef enum __qes_d_state_t { QES_DS_LESS_ZERO 
                              ,QES_DS_ZERO 
                              ,QES_DS_GTR_ZERO
                             } qes_d_state_t;

/* Return Value:
 * 0 - not same value
 * 1 -     same value
 */
int qes_same_value(double x1, double x2);

qes_d_state_t qes_solve(double a,
                        double b,
                        double c,
                        double* d_ptr,
                        double* x1_ptr,
                        double* x2_ptr);

#endif // ! defined QES_H_
