#include "printf_mt.h"

#include <pthread.h>

static pthread_mutex_t m_ = PTHREAD_MUTEX_INITIALIZER;

void printf_lock() {
  pthread_mutex_lock(&m_);
}

void printf_unlock() {
  pthread_mutex_unlock(&m_);
}
