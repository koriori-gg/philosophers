#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	printf("%ld %06d\n", tv.tv_sec, tv.tv_usec);
	usleep(10000);
	gettimeofday(&tv, NULL);
	printf("%ld %06d\n", tv.tv_sec, tv.tv_usec);
}