#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef POSIX_BARRIERS

#include "../barrier.h"

#else

typedef pthread_barrier_t barrier_t;

#define barrier_init(barrier, pshared, count)       \
  do {                                              \
    pthread_barrierattr_t attr;                     \
    pthread_barrierattr_setpshared(&attr, pshared); \
    pthread_barrier_init(barrier, &attr, count);    \
  } while (0)
#define barrier_destroy(barrier) pthread_barrier_destroy(barrier)
#define barrier_wait(barrier) pthread_barrier_wait(barrier)

#endif //POSIX_BARRIERS

#define NUM_THREADS 4

struct thread_args {
    int thread_idx;
    int sleep_time;
    barrier_t *barrier;
};

void *thread_fn(void *arg) {
  struct thread_args *args = (struct thread_args *) arg;
  usleep(args->sleep_time);
  printf("Thread %d slept for %d milliseconds\n", args->thread_idx, args->sleep_time / 1000);
  barrier_wait(args->barrier);
  pthread_exit(NULL);
}

int main() {
  barrier_t barrier;
  barrier_init(&barrier, 0, NUM_THREADS + 1);

  srand(time(NULL));

  pthread_t threads[NUM_THREADS];
  struct thread_args args[NUM_THREADS] = {
      {1, rand() % 100000, &barrier},
      {2, rand() % 100000, &barrier},
      {3, rand() % 100000, &barrier},
      {4, rand() % 100000, &barrier},
  };

  for (int i = 0; i < NUM_THREADS; ++i) {
    pthread_create(&threads[i], NULL, thread_fn, &args[i]);
  }

  barrier_wait(&barrier);
  printf("All threads have woken up\n");

  for (int i = 0; i < NUM_THREADS; ++i) {
    pthread_join(threads[i], NULL);
  }

  barrier_destroy(&barrier);
  return 0;
}
