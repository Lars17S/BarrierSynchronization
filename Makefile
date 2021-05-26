CC = gcc
CFLAGS = -lpthread
COMMON_FILES = parallel_sum.c numbers_list.h barrier.h

all: parallel_sum_custom parallel_sum_posix

parallel_sum_custom: $(COMMON_FILES) barrier.c
	$(CC) -o parallel_sum_custom $(CFLAGS) $(COMMON_FILES) barrier.c

parallel_sum_posix: $(COMMON_FILES)
	$(CC) -o parallel_sum_posix -DPOSIX_BARRIERS $(CFLAGS) $(COMMON_FILES)

clean:
	-rm parallel_sum_posix parallel_sum_custom *.o
