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

#endif // POSIX_BARRIERS

#define NUM_THREADS 4

#define NUMBERS_LIST_SIZE 8192
int numbers_list[NUMBERS_LIST_SIZE];
// The limits were purposely left unequal so that some threads
// take more time finishing the task
static const int limits[] = {0, 16, 128, 1024, NUMBERS_LIST_SIZE};

struct thread_args {
    int thread_idx;
    barrier_t *barrier;
    int *list_iterator;
    int *list_end;
    long long total;
};

void *thread_fn(void *arg) {
  struct thread_args *args = (struct thread_args *) arg;
  while (args->list_iterator != args->list_end) {
    usleep(*(args->list_iterator));
    args->total += *(args->list_iterator);
    ++(args->list_iterator);
  }
  printf("Thread %d finished the sum with a total of %lld\n",
         args->thread_idx, args->total);
  barrier_wait(args->barrier);
  pthread_exit(NULL);
}

int main() {
  barrier_t barrier;
  barrier_init(&barrier, 0, NUM_THREADS + 1);

  srand(0);
  for (int i = 0; i < NUMBERS_LIST_SIZE; ++i) {
    numbers_list[i] = rand() % 100;
  }

  pthread_t threads[NUM_THREADS];
  struct thread_args args[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; ++i) {
    args[i].thread_idx = i + 1;
    args[i].barrier = &barrier;
    args[i].list_iterator = numbers_list + limits[i];
    args[i].list_end = numbers_list + limits[i + 1];
    args[i].total = 0;
  }

  for (int i = 0; i < NUM_THREADS; ++i) {
    pthread_create(&threads[i], NULL, thread_fn, &args[i]);
  }

  barrier_wait(&barrier);
  long long total_sum = 0;
  for (int i = 0; i < NUM_THREADS; ++i) {
    total_sum += args[i].total;
  }
  printf("The total sum is %lld\n", total_sum);

  for (int i = 0; i < NUM_THREADS; ++i) {
    pthread_join(threads[i], NULL);
  }

  barrier_destroy(&barrier);
  return 0;
}
