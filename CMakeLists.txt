cmake_minimum_required(VERSION 3.0)
project(BarrierSynchronization C)
set(CMAKE_C_STANDARD 11)

set(BARRIER_SRC_FILES barrier.h barrier.c)

# Parallel sum example
add_executable(parallel_sum_custom examples/parallel_sum.c ${BARRIER_SRC_FILES})
target_link_libraries(parallel_sum_custom pthread)

add_executable(parallel_sum_posix examples/parallel_sum.c)
target_compile_definitions(parallel_sum_posix PRIVATE POSIX_BARRIERS)
target_link_libraries(parallel_sum_posix pthread)

# Sleepy threads example
add_executable(sleepy_threads_custom examples/sleepy_threads.c ${BARRIER_SRC_FILES})
target_link_libraries(sleepy_threads_custom pthread)

add_executable(sleepy_threads_posix examples/sleepy_threads.c)
target_compile_definitions(sleepy_threads_posix PRIVATE POSIX_BARRIERS)
target_link_libraries(sleepy_threads_posix pthread)

# Parallel sum test
add_executable(parallel_sum_test_barrier tests/parallel_sum_test.c ${BARRIER_SRC_FILES})
target_link_libraries(parallel_sum_test_barrier pthread)

add_executable(parallel_sum_test_no_barrier tests/parallel_sum_test.c)
target_compile_definitions(parallel_sum_test_no_barrier PRIVATE NO_BARRIER)
target_link_libraries(parallel_sum_test_no_barrier pthread)

# Thousand threads waiting benchmark
add_executable(thousand_threads_custom benchmarks/thousand_threads_waiting.c ${BARRIER_SRC_FILES})
target_link_libraries(thousand_threads_custom pthread)

add_executable(thousand_threads_posix benchmarks/thousand_threads_waiting.c)
target_compile_definitions(thousand_threads_posix PRIVATE POSIX_BARRIERS)
target_link_libraries(thousand_threads_posix pthread)
