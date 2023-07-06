#include "philo.h"

void	*philo_life_cycle(void *arg)
{
	t_philo	*philo;
	int		error;

	philo = (t_philo *)arg;
	error = 0;
	wait_start_time(philo->simulation->start);
	while (error == 0 && !should_stop(philo))
	{
		if (is_same_state(philo, SLEEP))
			error = philo_think(philo);
		else if (is_same_state(philo, THINK))
			error = philo_eat(philo);
		else if (is_same_state(philo, EAT))
			error = philo_sleep(philo);
		else
			error = -1;
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
		// if (simulation->must_eat != -1 && has_finished_eat(simulation))
		// 	break ;
		now = get_time();
		pthread_mutex_lock(&(simulation->philo[i].philo_mutex));
		if (now - simulation->philo[i].last_eat_time >= simulation->time_to_die)
		{
			pthread_mutex_lock(&(simulation->stop_mutex));
			simulation->stop = true;
			print_message(&(simulation->philo[i]), simulation->philo[i].id, now, "died");
			pthread_mutex_unlock(&(simulation->stop_mutex));
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
