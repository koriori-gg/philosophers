#include "philo.h"

static long	set_wait_time(t_simulation *simulation, int id)
{
	if (simulation->num_philo % 2 == 0)
	{
		if (id % 2 == 1)
			return (0);
		else
			return (simulation->time_to_eat);
	}
	if (id % 2 == 1 && id == 1)
		return (0);
	else if (id % 2 == 1 && id == simulation->num_philo)
		return (simulation->time_to_eat);
	else if (id % 2 == 1)
		return (simulation->time_to_eat / 2);
	if (id == simulation->num_philo - 1)
		return (simulation->time_to_eat * 2);
	else
		return (simulation->time_to_eat * 3 / 2);
}

static void	init_philo(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->num_philo)
	{
		simulation->philo[i].id = i + 1;
		simulation->philo[i].eat_count = 0;
		simulation->philo[i].state = SLEEP;
		simulation->philo[i].last_eat_time = simulation->start;
		simulation->philo[i].next_eat_time = simulation->start + set_wait_time(simulation, i + 1);
		simulation->philo[i].ideal_time = simulation->start;
		pthread_mutex_init(&(simulation->philo[i].philo_mutex), NULL);
		pthread_mutex_init(&(simulation->philo[i].l_fork), NULL);
		if (i > 0)
			simulation->philo[i].r_fork = &(simulation->philo[i - 1].l_fork);
		if (i + 1 == simulation->num_philo)
			simulation->philo[0].r_fork = &(simulation->philo[i].l_fork);
		simulation->philo[i].simulation = simulation;
		i++;
	}
}

static void	init_monitor(t_simulation *simulation)
{
	simulation->monitor->stop = false;
	pthread_mutex_init(&(simulation->monitor->stop_mutex), NULL);
	simulation->monitor->simulation = simulation;
}

int	init_simulation(int argc, char **argv, t_simulation *simulation)
{
	simulation->num_philo = ft_atol(argv[1]);
	simulation->time_to_die = ft_atol(argv[2]);
	simulation->time_to_eat = ft_atol(argv[3]);
	simulation->time_to_sleep = ft_atol(argv[4]);
	simulation->start = get_time() + 2000;
	simulation->must_eat = -1;
	if (argc == 6)
		simulation->must_eat = ft_atol(argv[5]);
	simulation->philo = (t_philo *)malloc
		(sizeof(t_philo) * simulation->num_philo);
	simulation->monitor = (t_monitor *)malloc(sizeof(t_monitor));
	if (!simulation->philo || !simulation->monitor)
		return (-1);
	init_philo(simulation);
	init_monitor(simulation);
	return (0);
}
