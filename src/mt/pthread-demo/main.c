#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils.h"

static void* release_proc(void* arg) {
  printf("release_proc\n");
  struct big_calc_data_t * pdata = (struct big_calc_data_t*) arg;
  big_calc_data_release(pdata);
  return NULL;
}

static void* thread_proc(void* arg) {
  (void) arg;

  pthread_t thread = pthread_self();
  printf("thread_proc: %ld\n", thread);


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
  const size_t ARRAY_SIZE = 1000;
  const size_t REALIZ_COUNT = 100000;

  big_calc_data_malloc(&big_calc_data, ARRAY_SIZE);

  for (size_t i = 0; i < REALIZ_COUNT; ++i) {
   if (i % 10 == 0) {
     pthread_testcancel();

     // printf is also cancellation point
     //fprintf(stdout, "Iteration: %ld.  ", i);
     //fflush(stdout);
   }
   do_big_calculation(&big_calc_data);
  }

  printf("out_acc_am[0]=%f\n", big_calc_data.out_acc_am[0]);

  printf("end of big calculation.\n");

  pthread_cleanup_pop(0);

  big_calc_data_release(&big_calc_data);

  return NULL;
}

int main() {
  printf("pthread demo\n");

  srand((unsigned int)time(NULL));

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
