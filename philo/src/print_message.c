#include "philo.h"

bool	print_message(t_philo *philo, long now)
{
	long	time;

	if (should_stop(philo))
		return (false);
	time = now - philo->simulation->start;
	pthread_mutex_lock(&(philo->simulation->state_mutex));
	if (philo->state == WAIT || philo->state == READY)
		printf("%ld %ld has taken a fork\n", time, philo->id);
	if (philo->state == EAT)
		printf("%ld %ld is eating\n", time, philo->id);
	if (philo->state == SLEEP)
		printf("%ld %ld is sleeping\n", time, philo->id);
	if (philo->state == THINK)
		printf("%ld %ld is thinking\n", time, philo->id);
	if (philo->state == DIED)
		printf("%ld %ld died\n", time, philo->id);
	pthread_mutex_unlock(&(philo->simulation->state_mutex));
	return (true);
}
