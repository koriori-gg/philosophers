#include "philo.h"

void	print_dead(t_philo *philo,long id, long now, char *message)
{
	long	time;

	time = now - philo->simulation->start;
	printf("%ld %ld %s\n", time, id, message);
}

int	update_philo(t_philo *philo, char *message, int state)
{
	long	time;
	int		stop;

	pthread_mutex_lock(&(philo->simulation->stop_mutex));
	stop = 0;
	philo->now = get_time();
	time = philo->now - philo->simulation->start;
	if (should_stop(philo))
		stop = -1;
	if (stop == 0)
		printf("%ld %ld %s\n", time, philo->id, message);
	if (state == EAT)
	{
		update_last_eat_time(philo, philo->now);
		add_eat_count(philo);
	}
	pthread_mutex_unlock(&(philo->simulation->stop_mutex));
	return (stop);
}
