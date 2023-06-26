#include "philo.h"

void	*philo_life_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_start_time(philo->simulation->start);
	wait_time(philo->simulation->start, philo->wait_time);
	while (!is_dead(philo) && !has_finished_eat(philo))
	{
		philo_take_fork(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	monitor(t_simulation *simulation)
{
	long	i;
	long	now;

	i = 0;
	wait_start_time(simulation->start);
	while (1)
	{
		now = get_time();
		if (now - simulation->philo[i].last_eat_time >= simulation->time_to_die)
		{
			update_philo(&(simulation->philo[i]), DIED, now);
			break ;
		}
		i++;
		if (simulation->num_philo == i)
			i = 0;
	}
}

void	start_simulation(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->num_philo)
	{
		pthread_create(&simulation->philo[i].thread, NULL,
			philo_life_cycle, &(simulation->philo[i]));
		i++;
	}
	monitor(simulation);
}

void	stop_simulation(t_simulation *simulation)
{
	int	i;

	ft_pthread_mutex_destroy(&simulation->mutex);
	i = 0;
	while (i < simulation->num_philo)
	{
		ft_pthread_mutex_destroy(&(simulation->philo[i].l_fork));
		ft_pthread_join(simulation->philo[i].thread);
		i++;
	}
	free(simulation->philo);
}
