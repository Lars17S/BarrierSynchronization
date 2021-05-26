cmake_minimum_required(VERSION 3.0)
project(BarrierSynchronization C)

set(CMAKE_C_STANDARD 11)

add_executable(parallel_sum_custom parallel_sum.c barrier.h barrier.c)

add_executable(parallel_sum_posix parallel_sum.c barrier.h)
target_compile_definitions(parallel_sum_posix PRIVATE POSIX_BARRIERS)
