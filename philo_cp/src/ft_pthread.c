#include "philo.h"

int	ft_pthread_create(pthread_t *thread, void *func, t_philo *philo_i, int i)
{
	if (pthread_create(thread, NULL, func, philo_i) != 0)
	{
		stop_simulation(philo_i->simulation, i);
		return (-1);
	}
	return (0);
}
