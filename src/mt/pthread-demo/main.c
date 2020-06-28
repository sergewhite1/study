#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "utils.h"

#define VK_ESCAPE       0x1B // esc key

static void* release_proc(void* arg) {
  printf("release_proc\n");
  struct big_calc_data_t * pdata = (struct big_calc_data_t*) arg;
  big_calc_data_release(pdata);
}

static void* thread_proc(void* arg) {
  pthread_t thread = pthread_self();
  printf("thread_proc: %ld\n", thread);

  const int N = 1000;

  struct big_calc_data_t big_calc_data;
  big_calc_data_init(&big_calc_data);

  pthread_cleanup_push( (void*) release_proc, &big_calc_data);

  for (int i = 10; i >= 0; --i) {
    fprintf(stdout, "%d ", i);
    fflush(stdout);

    // sleep - is cancellation point
    // otherwise use pthread_testcancel
    sleep(1);
  }

  printf("\n");

  printf("start of big calculation...\n");

  big_calc_data_malloc(&big_calc_data, N);

  for (size_t i = 0; i < 1000; ++i) {
   do_big_calculation(&big_calc_data);
  }

  printf("end of bif calculation.\n");

  pthread_cleanup_pop(0);

  big_calc_data_release(&big_calc_data);

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
