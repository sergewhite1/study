#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils.h"

#define VK_ESCAPE       0x1B // esc key

static void* release_proc(void* arg) {
  printf("release_proc\n");
}

static void do_big_calculation(size_t N,
  double* inp_cur_re, double* inp_cur_im, double* inp_cur_am,
  double* inp_sum_re, double* inp_sum_im, double* inp_sum_am,
  double* out_cur_re, double* out_cur_im, double* out_cur_am,
  double* out_sum_re, double* out_sum_im, double* out_sum_am) {
}

static void* thread_proc(void* arg) {
  pthread_t thread = pthread_self();
  printf("thread_proc: %ld\n", thread);

  const int N = 1000;

  double *inp_cur_re = NULL;
  double *inp_cur_im = NULL;
  double *inp_cur_am = NULL;

  double *inp_sum_re = NULL;
  double *inp_sum_im = NULL;
  double *inp_sum_am = NULL;

  double *out_cur_re = NULL;
  double *out_cur_im = NULL;
  double *out_cur_am = NULL;

  double *out_sum_re = NULL;
  double *out_sum_im = NULL;
  double *out_sum_am = NULL;

  pthread_cleanup_push( (void*) release_proc, NULL);

  for (int i = 10; i >= 0; --i) {
    fprintf(stdout, "%d ", i);
    fflush(stdout);

    // sleep - is cancellation point
    // otherwise use pthread_testcancel
    sleep(1);
  }

  printf("start of big calculation...\n");

  zero_array(N, inp_sum_re);
  zero_array(N, inp_sum_im);
  zero_array(N, inp_sum_am);

  zero_array(N, out_sum_re);
  zero_array(N, out_sum_im);
  zero_array(N, out_sum_am);

  for (size_t i = 0; i < 1000; ++i) {
   do_big_calculation(N,
     inp_cur_re, inp_cur_im, inp_cur_am,
     inp_sum_re, inp_sum_im, inp_sum_am,
     out_cur_re, out_cur_im, out_cur_am,
     out_sum_re, out_sum_im, out_sum_am);
  }

  printf("end of bif calculation.\n");

  pthread_cleanup_pop(0);

  free(inp_cur_re);
  free(inp_cur_im);
  free(inp_cur_am);

  free(inp_sum_re);
  free(inp_sum_im);
  free(inp_sum_am);

  free(out_cur_re);
  free(out_cur_im);
  free(out_cur_am);

  free(out_sum_re);
  free(out_sum_im);
  free(out_sum_am);

  return NULL;
}

int main() {
  printf("pthread demo\n");

  pthread_t thread = pthread_self();
  printf("Main thread: %ld\n", thread);

  int res = pthread_create(&thread, NULL, thread_proc, NULL);
  if (res == 0) {
    printf("New thread was created successfuly (%ld)\n", thread);
  } else {
    printf("Error: pthread_create res=%d\n", res);
  }

  printf("Press <ESC> for cancel.\n");

  int c = getch();
  if (c == VK_ESCAPE) {
    res = pthread_cancel(thread);
    if (res != 0) {
      printf("Error: pthread_cancel res=%d\n", res);
    }
  }

  pthread_join(thread, NULL);

  printf("\n");

  return 0;
}
