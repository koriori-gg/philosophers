#include "philo.h"

long	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	// printf("%ld\n", tv.tv_sec * 1000 +  tv.tv_usec / 1000);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	wait_start_time(long start)
{
	printf("%ld\n", start);
	while (1)
	{
		if (get_time() >= start)
			break ;
	}
}

void	wait_time(long now, long time)
{
	while (1)
	{
		if (now + time >= get_time())
			return ;
	}
}