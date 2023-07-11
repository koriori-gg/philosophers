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

	remain = time * 1000;
	while (remain > 0)
	{
		usleep((useconds_t)(remain / 2));
		now = get_time();
		remain = (start + time - now) * 1000;
	}
}

void	ideal_wait_time(t_philo *philo, int state)
{
	long	dt;

	if (state == THINK)
	{
		dt = philo->ideal_time - philo->now;
		wait_time(philo->now, philo->next_eat_time - philo->now + dt);
		philo->ideal_time = philo->next_eat_time;
	}
	if (state == EAT)
	{
		dt = philo->ideal_time - philo->now;
		wait_time(philo->now, philo->simulation->time_to_eat + dt);
		philo->ideal_time += philo->simulation->time_to_eat;
	}
	if (state == SLEEP)
	{
		dt = philo->ideal_time - philo->now;
		wait_time(philo->now, philo->simulation->time_to_sleep + dt);
		philo->ideal_time += philo->simulation->time_to_sleep;
	}
}
