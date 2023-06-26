#include "philo.h"

int	free_philo(t_simulation *simulation, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_join(simulation->philo[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	free_fork(t_simulation *simulation, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_destroy(&(simulation->philo[i].l_fork)) != 0)
			return (-1);
		i++;
	}
	return (0);
}