#include "philo.h"

bool	print_message(t_philo *philo, long now)
{
	long	time;

	if (philo->simulation->stop)
		return (false);
	if (philo->state == EAT)
		time = philo->last_eat_time - philo->simulation->start;
	else
		time = now - philo->simulation->start;
	if (philo->state == WAIT || philo->state == READY)
		printf("%ld %ld has taken a fork\n", time, philo->id);
	if (philo->state == EAT)
		printf("%ld %ld is eating\n", time, philo->id);
	if (philo->state == SLEEP)
		printf("%ld %ld is sleeping\n", time, philo->id);
	if (philo->state == THINK)
		printf("%ld %ld is thinking\n", time, philo->id);
	if (philo->state == DIED)
	{
		printf("%ld %ld died\n", time, philo->id);
		philo->simulation->stop = true;
	}
	return (true);
}
