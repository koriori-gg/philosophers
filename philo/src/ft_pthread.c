#include "philo.h"

void	ft_pthread_mutex_lock(pthread_mutex_t *mtx)
{
	if (pthread_mutex_lock(mtx) != 0)
		exit(1);
}

void	ft_pthread_mutex_unlock(pthread_mutex_t *mtx)
{
	if (pthread_mutex_unlock(mtx) != 0)
		exit(1);
}

int	ft_pthread_mutex_destroy(pthread_mutex_t *mtx)
{
	if (pthread_mutex_destroy(mtx) != 0)
		return (-1);
	return (0);
}

int	ft_pthread_create(pthread_t *thread, void *func, t_philo *philo_i, int i)
{
	if (pthread_create(thread, NULL, func, philo_i) != 0)
	{
		stop_simulation(philo_i->simulation, i);
		return (-1);
	}
	return (0);
}

void	ft_pthread_join(pthread_t thread)
{
	if (pthread_join(thread, NULL) != 0)
		exit(1);
}
