# Barrier Synchronization

Barrier synchronization is a concurrency issue used in parallel applications that involve processes and threads. This project contains a custom implementation of a barrier in C.

## Examples

We have included two examples: `parallel_sum` and `sleepy_threads`.

Each example has two versions: `[example]_custom` and `[example]_posix` with our custom implementation of a memory barrier and the POSIX implementation respectively.

To compile all the examples you can run `make examples` or to compile only one you can run:

- `make parallel_sum_custom`
- `make parallel_sum_posix`
- `make sleepy_threads_custom`
- `make sleepy_threads_posix`

## Benchmarks

We also included a benchmark named `thousand_threads_waiting.c`. It creates a thousand threads, makes the last one sleep for 10 milliseconds and then wakes all the threads up. You can compile both versions with the command `make thousand_threads` and then comparing how long they take to execute.

Here's our results comparing both programs with `hyperfine` in a computer with an i5-8250U:

| Command                     |  Mean [ms] | Min [ms] | Max [ms] |    Relative |
| :-------------------------- | ---------: | -------: | -------: | ----------: |
| `./thousand_threads_custom` | 39.8 ± 1.1 |     37.8 |     42.3 |        1.00 |
| `./thousand_threads_posix`  | 40.7 ± 1.2 |     38.3 |     43.6 | 1.02 ± 0.04 |

We can observe a 2% speedup over the POSIX implementation.

## Team

- Mario Emilio Jiménez Vizcaíno A01173359
- Kevin Torres Martínez A01656257
- Arturo Efrén Jiménez Garibaldi A00824428
- Roberto Rivera Terán A00369870
