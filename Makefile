CC = gcc

parallel_sum_custom: parallel_sum.c barrier.h barrier.c
	$(CC) -o parallel_sum_custom parallel_sum.c barrier.h barrier.c

parallel_sum_posix: parallel_sum.c barrier.h
	$(CC) -o parallel_sum_posix -DPOSIX_BARRIERS parallel_sum.c barrier.h
