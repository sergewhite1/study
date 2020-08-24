#include "utils.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

/* reads from keypress, doesn't echo */
/* https://stackoverflow.com/questions/3276546/how-to-implement-getch-function-of-c-in-linux*/
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

static void arr_zero(size_t N, double *arr) {
  for (size_t i = 0; i < N; ++i) {
    arr[i] = 0.0;
  }
}

static void arr_acc(size_t N, const double* arr_cur, double* arr_acc) {
  for (size_t i = 0; i < N; ++i) {
    arr_acc[i] += arr_cur[i];
  }
}

static double generate_random() {
  return (double) rand() / RAND_MAX;
}

static void generate_input(size_t N, double* arr_re, double* arr_im) {
  for (size_t i = 0; i < N; ++i) {
    arr_re[i] = generate_random();
    arr_im[i] = generate_random();
  }
}

static void dft(size_t N, const double* inp_re, const double* inp_im,
                                double* out_re,       double* out_im) {
  arr_zero(N, out_re);
  arr_zero(N, out_im);

  for (size_t k = 0; k < N; ++k) {
    for (size_t n = 0; n < N; ++n) {
      out_re[k] += inp_re[n] * cos(2 * M_PI * k * n / N) +
                   inp_im[n] * sin(2 * M_PI * k * n / N);

      out_im[k] -= inp_re[n] * sin(2 * M_PI * k * n / N) +
                   inp_im[n] * cos(2 * M_PI * k * n / N);
    }
  }
}

static void calc_amp(size_t N, const double *re, const double *im,
                     double *am) {
  for(size_t i = 0; i < N; ++i) {
    am[i] = hypot(re[i], im[i]);
  }
}

void big_calc_data_init(struct big_calc_data_t* pdata) {
  memset(pdata, 0, sizeof(*pdata));
}

int big_calc_data_malloc(struct big_calc_data_t* pdata, size_t N) {
  pdata->N = N;
  pdata->inp_cur_re = (double*) malloc(N * sizeof(double));
  pdata->inp_cur_im = (double*) malloc(N * sizeof(double));
  pdata->inp_cur_am = (double*) malloc(N * sizeof(double));

  pdata->inp_acc_re = (double*) malloc(N * sizeof(double));
  pdata->inp_acc_im = (double*) malloc(N * sizeof(double));
  pdata->inp_acc_am = (double*) malloc(N * sizeof(double));

  pdata->out_cur_re = (double*) malloc(N * sizeof(double));
  pdata->out_cur_im = (double*) malloc(N * sizeof(double));
  pdata->out_cur_am = (double*) malloc(N * sizeof(double));

  pdata->out_acc_re = (double*) malloc(N * sizeof(double));
  pdata->out_acc_im = (double*) malloc(N * sizeof(double));
  pdata->out_acc_am = (double*) malloc(N * sizeof(double));

  arr_zero(N, pdata->inp_acc_re);
  arr_zero(N, pdata->inp_acc_im);
  arr_zero(N, pdata->inp_acc_am);

  arr_zero(N, pdata->out_acc_re);
  arr_zero(N, pdata->out_acc_im);
  arr_zero(N, pdata->out_acc_am);

  return 0;
}

void big_calc_data_release(struct big_calc_data_t* pdata) {
  free(pdata->inp_cur_re);
  free(pdata->inp_cur_im);
  free(pdata->inp_cur_am);

  free(pdata->inp_acc_re);
  free(pdata->inp_acc_im);
  free(pdata->inp_acc_am);

  free(pdata->out_cur_re);
  free(pdata->out_cur_im);
  free(pdata->out_cur_am);

  free(pdata->out_acc_re);
  free(pdata->out_acc_im);
  free(pdata->out_acc_am);

  big_calc_data_init(pdata);
}

void do_big_calculation(struct big_calc_data_t* pdata) {
  generate_input(pdata->N, pdata->inp_cur_re, pdata->inp_cur_im);

  dft(pdata->N, pdata->inp_cur_re, pdata->inp_cur_im,
                pdata->out_cur_re, pdata->out_cur_im);

  calc_amp(pdata->N, pdata->inp_cur_re, pdata->inp_cur_im, pdata->inp_cur_am);
  calc_amp(pdata->N, pdata->out_cur_re, pdata->out_cur_im, pdata->out_cur_am);

  arr_acc(pdata->N, pdata->inp_cur_re, pdata->inp_acc_re);
  arr_acc(pdata->N, pdata->inp_cur_im, pdata->inp_acc_im);
  arr_acc(pdata->N, pdata->inp_cur_am, pdata->inp_acc_am);

  arr_acc(pdata->N, pdata->out_cur_re, pdata->out_acc_re);
  arr_acc(pdata->N, pdata->out_cur_im, pdata->out_acc_im);
  arr_acc(pdata->N, pdata->out_cur_am, pdata->out_acc_am);
}
