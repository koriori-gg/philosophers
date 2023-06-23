#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	wait_start_time(long start)
{
	while (1)
	{
		if (get_time() >= start)
			break ;
	}
}

void	wait_time(long now, long time)
{
	long	real_time;

	real_time = time * 2 / 3;
	while (1)
	{
		if (get_time() >= now + real_time)
			return ;
	}
}
