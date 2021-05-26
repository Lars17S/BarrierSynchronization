#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "barrier.h"
#include "numbers_list.h"

#define NUM_THREADS 4

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
  printf("Thread %d finished the sum with a total of %lld\n", args->thread_idx, args->total);
  barrier_wait(args->barrier);
  pthread_exit(NULL);
}

int main() {
  barrier_t barrier;
  barrier_init(&barrier, 0, NUM_THREADS + 1);

  pthread_t threads[NUM_THREADS];
  struct thread_args args[NUM_THREADS] = {
      {1, &barrier, numbers_list + numbers_list_limits[0], numbers_list + numbers_list_limits[1], 0},
      {2, &barrier, numbers_list + numbers_list_limits[1], numbers_list + numbers_list_limits[2], 0},
      {3, &barrier, numbers_list + numbers_list_limits[2], numbers_list + numbers_list_limits[3], 0},
      {4, &barrier, numbers_list + numbers_list_limits[3], numbers_list + numbers_list_limits[4], 0},
  };

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
