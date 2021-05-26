cmake_minimum_required(VERSION 3.0)
project(BarrierSynchronization C)
set(CMAKE_C_STANDARD 11)

set(COMMON_SOURCE_FILES parallel_sum.c barrier.h numbers_list.h)

add_executable(parallel_sum_custom ${COMMON_SOURCE_FILES} barrier.c)
target_link_libraries(parallel_sum_custom pthread)

add_executable(parallel_sum_posix ${COMMON_SOURCE_FILES})
target_compile_definitions(parallel_sum_posix PRIVATE POSIX_BARRIERS)
target_link_libraries(parallel_sum_posix pthread)
