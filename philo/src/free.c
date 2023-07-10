#include "philo.h"

static int	free_philo(t_simulation *simulation, int count)
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

static int	free_fork(t_simulation *simulation, int count)
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

static int	free_philo_mutex(t_simulation *simulation, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_destroy(&(simulation->philo[i].philo_mutex)) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	join_all_thread(t_simulation *simulation, int count)
{
	if (pthread_join(simulation->monitor->thread, NULL) != 0)
			return (-1);
	if (free_philo(simulation, count) != 0)
		return (-1);
	return (0);
}

int	free_all_mutex(t_simulation *simulation, int count)
{
	if (pthread_mutex_destroy(&simulation->monitor->stop_mutex) != 0)
		return (-1);
	if (free_fork(simulation, count) != 0)
		return (-1);
	if (free_philo_mutex(simulation, count) != 0)
		return (-1);
	return (0);
}