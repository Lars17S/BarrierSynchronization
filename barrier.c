#include "barrier.h"

#include <errno.h>
#include <malloc.h>

int barrier_init(barrier_t *barrier, int pshared, unsigned int count) {
  if (count <= 0) {
    return EINVAL;
  }
  if (barrier == NULL) {
    barrier = malloc(sizeof(barrier_t));
    if (barrier == NULL) {
      return ENOMEM;
    }
  }

  if (sem_init(&(barrier->semaphore), pshared, 0) != 0) {
    return errno;
  }
  barrier->threads_waiting = 0;
  barrier->threads_left = count;
  int mutex_error = pthread_mutex_init(&(barrier->thread_counters_mutex), NULL);
  if (mutex_error != 0) {
    return mutex_error;
  }

  return 0;
}

int barrier_destroy(barrier_t *barrier) {
  if (sem_destroy(&(barrier->semaphore)) != 0) {
    return errno;
  }
  int mutex_error = pthread_mutex_destroy(&(barrier->thread_counters_mutex));
  if (mutex_error != 0) {
    return mutex_error;
  }
  return 0;
}

int barrier_wait(barrier_t *barrier) {
  pthread_mutex_lock(&(barrier->thread_counters_mutex));

  if (barrier->threads_left == 1) {
    pthread_mutex_unlock(&(barrier->thread_counters_mutex));
    for (unsigned int i = 0; i < barrier->threads_waiting; ++i) {
      sem_post(&(barrier->semaphore));
    }
    return 0;
  }

  --(barrier->threads_left);
  ++(barrier->threads_waiting);
  pthread_mutex_unlock(&(barrier->thread_counters_mutex));
  return sem_wait(&(barrier->semaphore));
}

