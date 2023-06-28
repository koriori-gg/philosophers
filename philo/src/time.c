#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	wait_start_time(long start)
{
	useconds_t	remain;
	long		now;

	now = get_time();
	remain = (useconds_t)(start - now);
	while (remain > 0)
	{
		usleep(remain / 2);
		now = get_time();
		remain = (useconds_t)(start - now);
	}
}

void	wait_time(long start, long time)
{
	useconds_t	remain;
	long		now;

	remain = (useconds_t)time;
	while (remain > 0)
	{
		usleep(remain / 2);
		now = get_time();
		remain = (useconds_t)(start + time - now);
	}
}
