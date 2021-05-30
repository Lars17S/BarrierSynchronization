CC = gcc
CFLAGS = -lpthread

BARRIER_FILES = barrier.h barrier.c

all: parallel_sum sleepy_threads


# Parallel sum example
PARALLEL_SUM_FILES = examples/parallel_sum.c
parallel_sum: parallel_sum_custom parallel_sum_posix

parallel_sum_custom: $(PARALLEL_SUM_FILES) $(BARRIER_FILES)
	$(CC) -o parallel_sum_custom $(CFLAGS) $(PARALLEL_SUM_FILES) $(BARRIER_FILES)

parallel_sum_posix: $(COMMON_FILES)
	$(CC) -o parallel_sum_posix -DPOSIX_BARRIERS $(CFLAGS) $(PARALLEL_SUM_FILES)


# Sleepy threads example
SLEEPY_THREADS_FILES = examples/sleepy_threads.c
sleepy_threads: sleepy_threads_custom sleepy_threads_posix

sleepy_threads_custom:
	$(CC) -o sleepy_threads_custom $(CFLAGS) $(SLEEPY_THREADS_FILES) $(BARRIER_FILES)

sleepy_threads_posix:
	$(CC) -o sleepy_threads_posix -DPOSIX_BARRIERS $(CFLAGS) $(SLEEPY_THREADS_FILES)


clean:
	-rm \
		parallel_sum_posix parallel_sum_custom \
		sleepy_threads_custom sleepy_threads_posix
