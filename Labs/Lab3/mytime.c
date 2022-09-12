#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main(void) {
  struct timeval cur_time;
  gettimeofday(&cur_time, NULL);
  printf("%s\n", ctime(&cur_time.tv_sec));
  return 0;
}
