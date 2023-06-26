#include "philo.h"

void	free_philo(t_simulation *simulation, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		ft_pthread_join(simulation->philo[i].thread);
		i++;
	}
}

int	free_fork(t_simulation *simulation, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (ft_pthread_mutex_destroy(&(simulation->philo[i].l_fork)) == -1)
			return (-1);
		i++;
	}
	return (0);
}