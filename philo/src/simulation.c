#include "philo.h"

void	*alone_philo_life(t_philo *philo)
{
	int		stop;

	stop = 0;
	change_state(philo, THINK);
	while (stop == 0)
	{
		if (is_same_state(philo, THINK))
		{
			change_state(philo, EAT);
			stop = philo_take_fork(philo);
		}
		else if (!is_same_state(philo, THINK))
			stop = philo_think(philo);
	}
	return (NULL);
}

void	*philo_life_cycle(void *arg)
{
	t_philo	*philo;
	int		stop;

	philo = (t_philo *)arg;
	stop = 0;
	wait_start_time(philo->simulation->start);
	if (philo->simulation->num_philo == 1)
		return (alone_philo_life(philo));
	while (stop == 0)
	{
		if (is_same_state(philo, SLEEP))
			stop = philo_think(philo);
		else if (is_same_state(philo, THINK))
			stop = philo_eat(philo);
		else if (is_same_state(philo, EAT))
			stop = philo_sleep(philo);
	}
	put_down_fork(&(philo->l_fork), philo->r_fork);
	return (NULL);
}

int	start_simulation(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->num_philo)
	{
		if (pthread_create(&(simulation->philo[i].thread), NULL,
			philo_life_cycle, &(simulation->philo[i])) != 0)
		{
			stop_simulation(simulation, i);
				return (-1);
		}
		i++;
	}
	if(pthread_create(&(simulation->monitor->thread), NULL, monitor, simulation) != 0)
	{
		stop_simulation(simulation, simulation->num_philo);
		return (-1);
	}
	return (0);
}

int	stop_simulation(t_simulation *simulation, int count)
{
	join_all_thread(simulation, count);
	free_all_mutex(simulation, count);
	free(simulation->philo);
	free(simulation->monitor);
	return (0);
}
