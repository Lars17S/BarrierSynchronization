#ifndef BARRIERS_H
#define BARRIERS_H

#ifdef POSIX_BARRIERS

#include <pthread.h>

typedef pthread_barrier_t barrier_t;

#define barrier_init(barrier, count) pthread_barrier_init(barrier, NULL, count)
#define barrier_destroy(barrier) pthread_barrier_destroy(barrier)
#define barrier_wait(barrier) pthread_barrier_destroy(barrier)

#else //POSIX_BARRIERS

struct barrier_impl {
    // TODO: Add members
};

typedef struct barrier_impl barrier_t;

int barrier_init(barrier_t* barrier, unsigned count);
int barrier_destroy(barrier_t* barrier);
int barrier_wait(barrier_t* barrier);

#endif //POSIX_BARRIERS

#endif //BARRIERS_H
