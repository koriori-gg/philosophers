#include "philo.h"

void	print_message(t_philo *philo,long id, long now, char *message)
{
	long	time;

	time = now - philo->simulation->start;
	pthread_mutex_lock(&(philo->simulation->print_mutex));
	printf("%ld %ld %s\n", time, id, message);
	pthread_mutex_unlock(&(philo->simulation->print_mutex));
}
