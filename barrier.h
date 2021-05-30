#ifndef BARRIERS_H
#define BARRIERS_H

#include <pthread.h>
#include <semaphore.h>

struct barrier_impl {
    sem_t semaphore;
    unsigned int threads_waiting;
    unsigned int threads_left;
    pthread_mutex_t thread_counters_mutex;
};

typedef struct barrier_impl barrier_t;

/**
 * Initialize a barrier. The barrier is opened when COUNT waiters have arrived
 * @param barrier the pointer where the barrier will be stored
 * @param pshared if non-zero, the barrier can be shared between processes
 * @param count the number of waiters needed to open the barrier
 * @return 0 on success, else an error number
 */
int barrier_init(barrier_t *barrier, int pshared, unsigned int count);

/**
 * Destroy a previously initialized barrier
 * @param barrier the pointer where the barrier is stored
 * @return 0 on success, else an error number
 */
int barrier_destroy(barrier_t *barrier);

/**
 * Wait for every other waiter to arrive to the barrier
 * @param barrier the pointer where the barrier is stored
 * @return 0 on success, else an error number
 */
int barrier_wait(barrier_t *barrier);

#endif //BARRIERS_H
