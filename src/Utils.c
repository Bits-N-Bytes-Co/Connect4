#include <stdlib.h>

#include "../include/Utils.h"

#ifdef _WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif

double get_time() {
#ifdef _WIN32
  clock_t time = clock();
  return (double)time / CLOCKS_PER_SEC;
#else
  struct timeval time;
  gettimeofday(&time, NULL);
  return time.tv_sec + time.tv_usec / 1000000.0;
#endif
}

void delay(double time) {
  double start = get_time();
  while (get_time() - start < time)
    ;
}