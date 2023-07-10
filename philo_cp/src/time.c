#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	wait_start_time(long start)
{
	long	remain;
	long	now;

	now = get_time();
	remain = start - now;
	while (remain > 0)
	{
		usleep((useconds_t)(remain / 2));
		now = get_time();
		remain = start - now;
	}
}

void	wait_time(long start, long time)
{
	long	remain;
	long	now;

	remain = time;
	while (remain > 0)
	{
		usleep((useconds_t)(remain / 2));
		now = get_time();
		remain = start + time - now;
	}
}
