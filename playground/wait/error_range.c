#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

int64_t get_time(void)
{
  struct timeval tv;

  gettimeofday(&tv, NULL);
  return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000));
}

int main()
{
  int64_t time, time2;
  while (1)
  {
  time = get_time() + 100;
  usleep(100 * 1000);
  time2 = get_time();
  printf("%lld - %lld = %lld\n", time, time2, time - time2);
  }
}
