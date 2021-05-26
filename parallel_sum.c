#include <stdio.h>
#include <pthread.h>

#include "barrier.h"

int main() {
  printf("Hello, World!\n");
#ifdef POSIX_BARRIERS
  printf("posix_barriers\n");
#else
  printf("custom barriers\n");
#endif
  return 0;
}
