#include "philo.h"

int	is_dead(t_philo *philo)
{
	long	now;

	now = get_time();
	if (now - philo->last_eat_time >= philo->simulation->time_to_die)
		return (-1);
	return (0);
}

void	print_dead(t_philo *philo,long id, long now, char *message)
{
	long	time;

	time = now - philo->simulation->start;
	printf("%ld %ld %s\n", time, id, message);
}

int	print_action(t_philo *philo, char *message)
{
	long	time;
	int		stop;

	stop = 0;
	pthread_mutex_lock(&(philo->simulation->stop_mutex));
	philo->now = get_time();
	time = philo->now - philo->simulation->start;
	if (should_stop(philo))
		stop = -1;
	if (stop == 0)
		printf("%ld %ld %s\n", time, philo->id, message);
	pthread_mutex_unlock(&(philo->simulation->stop_mutex));
	return (stop);
}
