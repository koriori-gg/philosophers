#include "philo.h"

void	*philo_life_cycle(void *arg)
{
	t_philo	*philo;
	int		stop;

	philo = (t_philo *)arg;
	stop = 0;
	wait_start_time(philo->simulation->start);
	while (stop == 0)
	{
		if (is_same_state(philo, SLEEP))
			stop = philo_think(philo);
		else if (is_same_state(philo, THINK))
			stop = philo_eat(philo);
		else if (is_same_state(philo, EAT))
			stop = philo_sleep(philo);
		else
			stop = -1;
	}
	put_down_fork(&(philo->l_fork), philo->r_fork);
	return (NULL);
}

bool	check_philo(t_simulation *simulation)
{
	long	i;
	bool	need;
	long	now;

	i = 0;
	need = true;
	while (i < simulation->num_philo && need)
	{
		pthread_mutex_lock(&simulation->philo[i].philo_mutex);
		pthread_mutex_lock(&simulation->monitor->stop_mutex);
		now = get_time();
		if (now - simulation->philo[i].last_eat_time >= simulation->time_to_die)
		{
			print_dead(now - simulation->start, simulation->philo[i].id, "is dead");
			simulation->monitor->stop = true;
			need = false;
		}
		pthread_mutex_unlock(&simulation->monitor->stop_mutex);
		pthread_mutex_unlock(&simulation->philo[i].philo_mutex);
		i++;
	}
	return (need);
}

void	*monitor(void *arg)
{
	t_simulation	*simulation;
	bool			need_to_continue;

	simulation = (t_simulation *)arg;
	need_to_continue = true;
	while (need_to_continue)
	{
		usleep(1000);
		need_to_continue = check_philo(simulation);
	}
	return (NULL);
}

int	start_simulation(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->num_philo)
	{
		if (pthread_create(&simulation->philo[i].thread, NULL,
			philo_life_cycle, &(simulation->philo[i])) != 0)
		{
			stop_simulation(simulation, i);
				return (-1);
		}
		i++;
	}
	if(pthread_create(&simulation->monitor->thread, NULL, monitor, simulation) != 0)
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
