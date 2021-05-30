# Barrier Synchronization

Barrier synchronization is a concurrency issue used in parallel applications that involve processes and threads. This
project contains a custom implementation of a barrier in C.

## Examples

We have included two examples: `parallel_sum` and `sleepy_threads`.

Each example has two versions: `[example]_custom` and `[example]_posix` with our custom implementation of a memory
barrier and the POSIX implementation respectively.

To compile all the examples you can run `make all` or to compile only one you can run:

- `make parallel_sum_posix`
- `make parallel_sum_custom`
- `make sleepy_threads_posix`
- `make sleepy_threads_custom`

## Team

- Mario Emilio Jiménez Vizcaíno A01173359
- Kevin Torres Martínez A01656256
- Arturo Efrén Jiménez Garibaldi A00824428
- Roberto Rivera Terán A00369870
