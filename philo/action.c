#include "philo.h"
//usleep μs -> x100 = ms
void	take_a_fork()
{
	struct timeval tv;

	if (gettimeofday(&tv , NULL))
		printf("error\n");
	printf("%ld has taken a fork\n", tv.tv_sec);
}
void eating(t_philo	*philo)
{
	struct timeval tv;

	if (gettimeofday(&tv , NULL))
		printf("error\n");
	printf("%ld is eating\n", tv.tv_sec);
	usleep(philo->time_to_eat * 1000);
}

void sleeping(t_philo *philo)
{
	struct timeval tv;

	if (gettimeofday(&tv , NULL))
		printf("error\n");
	printf("%ld is sleeping\n", tv.tv_sec);
	usleep(philo->time_to_sleep * 1000);
}

void thinking(t_philo *philo)
{
	struct timeval tv;

	(void)philo;
	if (gettimeofday(&tv , NULL))
		printf("error\n");
	printf("%ld is thinking\n", tv.tv_sec);
}
