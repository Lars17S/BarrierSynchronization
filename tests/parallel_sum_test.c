#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef NO_BARRIER

#include "../barrier.h"

#else

typedef void* barrier_t;

#define barrier_init(barrier, pshared, count) do {} while(0)
#define barrier_destroy(barrier) do {} while(0)
#define barrier_wait(barrier) do {} while(0)

#endif // NO_BARRIER

#define NUM_THREADS 4

#define NUMBERS_PER_THREAD 100
#define NUMBERS_LIST_SIZE (NUM_THREADS * NUMBERS_PER_THREAD)

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
    args->total += *(args->list_iterator);
    ++(args->list_iterator);
  }
  barrier_wait(args->barrier);
  pthread_exit(NULL);
}

int main() {
#ifndef NO_BARRIER
  printf("Parallel sum test with barrier synchronization\n");
#else
  printf("Parallel sum test without barrier synchronization\n");
#endif // NO_BARRIER

  barrier_t barrier;
  barrier_init(&barrier, 0, NUM_THREADS + 1);

  int numbers_list[NUMBERS_LIST_SIZE];
  srand(0);
  for (int i = 0; i < NUMBERS_LIST_SIZE; ++i) {
    numbers_list[i] = rand() % 100;
  }

  pthread_t threads[NUM_THREADS];
  struct thread_args args[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; ++i) {
    args[i].thread_idx = i + 1;
    args[i].barrier = &barrier;
    args[i].list_iterator = numbers_list + (i * NUMBERS_PER_THREAD);
    args[i].list_end = numbers_list + ((i + 1) * NUMBERS_PER_THREAD);
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
  printf("Result:   %6lld\n", total_sum);

  long long expected_sum = 19709;
  printf("Expected: %6lld\n", expected_sum );
  if (total_sum == expected_sum) {
    printf("Test case passed\n");
  } else {
    printf("Test case failed\n");
  }

  for (int i = 0; i < NUM_THREADS; ++i) {
    pthread_join(threads[i], NULL);
  }

  barrier_destroy(&barrier);
  return 0;
}
