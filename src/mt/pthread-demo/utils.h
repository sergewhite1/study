#ifndef UTILS_H_
#define UTILS_H_

#include <stddef.h>

int getch(void);

struct big_calc_data_t {
  size_t N; // array size

  double *inp_cur_re;
  double *inp_cur_im;
  double *inp_cur_am;

  double *inp_acc_re;
  double *inp_acc_im;
  double *inp_acc_am;

  double *out_cur_re;
  double *out_cur_im;
  double *out_cur_am;

  double *out_acc_re;
  double *out_acc_im;
  double *out_acc_am;
};

void big_calc_data_init(struct big_calc_data_t* pdata);
int  big_calc_data_malloc(struct big_calc_data_t* pdata, size_t N);
void big_calc_data_release(struct big_calc_data_t* pdata);

void do_big_calculation(struct big_calc_data_t* pdata);

#endif // ! UTILS_H_

