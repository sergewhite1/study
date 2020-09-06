#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <sys/time.h>

#include "printf_mt.h"

static void print_desc() {
  const char FILENAME[] = "desc.txt";
  FILE * f = NULL;
  char * buffer = NULL;
  size_t buffer_size = 100;
  do {
    buffer = (char*) malloc(buffer_size * sizeof(char));
    if (buffer == NULL) {
      printf("Error of memory allocation.\n");
      break;
    }

    f = fopen(FILENAME, "rt");
    if (f == NULL) {
      printf("Error of opeening file: %s\n", FILENAME);
      break;
    }
    while (getline(&buffer, &buffer_size, f) != -1) {
      printf("%s", buffer);
    }
  } while (0);

  if (buffer != NULL) {
    free(buffer);
  }

  if (f != NULL) {
    fclose(f);
  }
}

const char* time_to_str(const struct timeval * tv_ptr) {
  static char ret[100];
  struct tm * tm_ptr = localtime(&tv_ptr->tv_sec);
  snprintf(ret, 100, "%d-%02d-%02d-%02d-%02d-%02d-%06ld",
           tm_ptr->tm_year + 1900,
           tm_ptr->tm_mon + 1,
           tm_ptr->tm_mday,
           tm_ptr->tm_hour,
           tm_ptr->tm_min,
           tm_ptr->tm_sec,
           tv_ptr->tv_usec
           );
  return ret;
}

#define SYNC_MAX_COUNT 10

static void syncronization_point() {
  static pthread_mutex_t sync_lock = PTHREAD_MUTEX_INITIALIZER;
  static pthread_cond_t sync_cond = PTHREAD_COND_INITIALIZER;
  static int sync_count = 0;

  pthread_mutex_lock(&sync_lock);
  sync_count++;

  if (sync_count < SYNC_MAX_COUNT) {
    pthread_cond_wait(&sync_cond, &sync_lock);
  } else {
    pthread_cond_broadcast(&sync_cond);
  }

  pthread_mutex_unlock(&sync_lock);
}

static void* thread_proc(void* arg) {
  syncronization_point();

  struct timeval tv;
  gettimeofday(&tv, NULL);
  int * thread_num = (int*)arg;

  printf_lock();
    printf("%s Thread proc # %d\n", time_to_str(&tv), *thread_num);
  printf_unlock();

  return NULL;
}

int main() {
  print_desc();

  printf("SYNC_MAX_COUNT=%d\n", SYNC_MAX_COUNT);

  printf("Press <ENTER> to continue...");
  getchar();

  pthread_t thread_id[SYNC_MAX_COUNT] = {0};

  int thread_num[SYNC_MAX_COUNT];
  for (int i = 0; i < SYNC_MAX_COUNT; ++i) {
    thread_num[i] = i;
  }

  for (int i = 0; i < SYNC_MAX_COUNT; ++i) {
    if (pthread_create(&thread_id[i], 
                       NULL,
                       thread_proc,
                       (void*)&thread_num[i]) != 0) {
      printf("Error of create thread! num=%d \n", i);
      return 1;
    }
  }

  for (int i = 0; i < SYNC_MAX_COUNT; ++i) {
    pthread_join(thread_id[i], NULL);
  }
  return 0;
}
