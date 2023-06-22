#include "philo.h"

static void init_philo(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->num_philo)
	{
		simulation->philo[i].id = i;
		simulation->philo[i].eat_count = 0;
		simulation->philo[i].last_eat_time = simulation->start;
		pthread_mutex_init(&(simulation->philo[i].l_fork), NULL);
		if (i > 0)
			simulation->philo[i].r_fork = &(simulation->philo[i - 1].l_fork);
		if (i == simulation->num_philo - 1)
			simulation->philo[0].r_fork = &(simulation->philo[i].l_fork);
		simulation->philo[i].simulation = simulation;
		i++;
	}
}

void	init_simulation(int argc, char **argv, t_simulation *simulation)
{
	simulation->num_philo = ft_atol(argv[1]);
	simulation->time_to_die = ft_atol(argv[2]);
	simulation->time_to_eat = ft_atol(argv[3]);
	simulation->time_to_sleep = ft_atol(argv[4]);
	simulation->start = get_time() + 1000;
	simulation->stop = false;
	pthread_mutex_init(&(simulation->mutex), NULL);
	if (argc == 6)
		simulation->must_eat = ft_atol(argv[5]);
	simulation->philo = (t_philo *)malloc(sizeof(t_philo) * simulation->num_philo);
	if (!simulation->philo)
		exit(1);
	init_philo(simulation);
}
