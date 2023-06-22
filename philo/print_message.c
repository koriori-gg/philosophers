#include "philo.h"

bool	print_message(t_philo *philo, long now)
{
	long	time;

	ft_pthread_mutex_lock(&(philo->simulation->mutex));
	if (philo->simulation->stop)
	{
		ft_pthread_mutex_unlock(&(philo->simulation->mutex));
		return (false);
	}
	time = now - philo->simulation->start;
	if (philo->state == WAIT)
		printf("%ld %ld has taken a fork\n", time, philo->id);
	if (philo->state == EAT)
		printf("%ld %ld is eating\n", time, philo->id);
	if (philo->state == SLEEP)
		printf("%ld %ld is sleeping\n", time, philo->id);
	if (philo->state == THINK)
		printf("%ld %ld is thinking\n", time, philo->id);
	if (philo->state == DIED)
		printf("%ld %ld died\n", time, philo->id);
	ft_pthread_mutex_unlock(&(philo->simulation->mutex));
	return (true);
}
