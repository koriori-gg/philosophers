#include "philo.h"

void	*philo_life_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_start_time(philo->simulation->start);
	while (!should_stop(philo))
	{
		philo_think(philo);
		philo_take_fork(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	put_down_fork(&(philo->l_fork), philo->r_fork);
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
		if (simulation->must_eat != -1 && has_finished_eat(simulation))
			break ;
		now = get_time();
		pthread_mutex_lock(&(simulation->philo[i].philo_mutex));
		if (now - simulation->philo[i].last_eat_time >= simulation->time_to_die)
		{
			print_message(&(simulation->philo[i]), simulation->philo[i].id, now, "died");
			update_stop(&(simulation->philo[i]));
			pthread_mutex_unlock(&(simulation->philo[i].philo_mutex));
			break ;
		}
		pthread_mutex_unlock(&(simulation->philo[i].philo_mutex));
		i++;
		if (simulation->num_philo == i)
			i = 0;
	}
}

int	start_simulation(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->num_philo)
	{
		if(ft_pthread_create(&simulation->philo[i].thread,
			philo_life_cycle, &(simulation->philo[i]), i) != 0)
				return (-1);
		i++;
	}
	monitor(simulation);
	return (0);
}

int	stop_simulation(t_simulation *simulation, int count)
{
	pthread_mutex_destroy(&simulation->print_mutex);
	pthread_mutex_destroy(&simulation->stop_mutex);
	if (free_fork(simulation, count) != 0)
		return (-1);
	if (free_philo(simulation, count) != 0)
		return (-1);
	free(simulation->philo);
	return (0);
}
