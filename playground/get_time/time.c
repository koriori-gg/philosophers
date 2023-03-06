#include <sys/time.h>
#include <stdio.h>

// int gettimeofday(struct timeval *tv, struct timezone *tz);

int main(void)
{
	struct timeval tv;

	if (gettimeofday(&tv , NULL))
		printf("error\n");
	printf("%ld %d\n", tv.tv_sec, tv.tv_usec);
	printf("%ld %d\n", tv.tv_sec, tv.tv_usec);
	//一回取得したら次のgettimeofdayまでは一緒の値
	gettimeofday(&tv, NULL);
	printf("%ld %d\n", tv.tv_sec, tv.tv_usec);
}