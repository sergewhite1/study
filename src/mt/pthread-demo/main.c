#include <pthread.h>
#include <stdio.h>

static void* thread_proc(void* arg) {
  pthread_t thread = pthread_self();
  printf("thread_proc: %ld\n", thread);

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

  for (int i = 10; i >= 0; --i) {
    printf("%d ", i);
  }
  printf("\n");

  pthread_join(thread, NULL);

  return 0;
}
