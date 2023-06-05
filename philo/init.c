#include "philo.h"

void	init_table(int argc, char **argv, t_table *table)
{
	(void)argc;
	table->num_philo = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->num_philo);
	if (!table->philo)
		exit(1);
}