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
		pthread_mutex_lock(&(simulation->last_eat_mutex));
		if (now - simulation->philo[i].last_eat_time >= simulation->time_to_die)
		{
			pthread_mutex_unlock(&(simulation->last_eat_mutex));
			change_state(&(simulation->philo[i]), DIED);
			print_message(&(simulation->philo[i]), now);
			update_stop(&(simulation->philo[i]));
			break ;
		}
		pthread_mutex_unlock(&(simulation->last_eat_mutex));
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
	pthread_mutex_destroy(&simulation->eat_count_mutex);
	pthread_mutex_destroy(&simulation->state_mutex);
	pthread_mutex_destroy(&simulation->stop_mutex);
	pthread_mutex_destroy(&simulation->last_eat_mutex);
	if (free_fork(simulation, count) != 0)
		return (-1);
	if (free_philo(simulation, count) != 0)
		return (-1);
	free(simulation->philo);
	return (0);
}
