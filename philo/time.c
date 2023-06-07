#include "philo.h"

long	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	// printf("%ld\n", tv.tv_sec * 1000 +  tv.tv_usec / 1000);
	return (tv.tv_sec * 1000 +  tv.tv_usec / 1000);
}
