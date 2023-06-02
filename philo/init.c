#include "philo.h"

void	init_philo(int argc, char **argv, t_philo *philo)
{
	(void)argc;
	philo->number_of_philosophers = ft_atol(argv[1]);
	philo->time_to_die = ft_atol(argv[2]);
	philo->time_to_eat = ft_atol(argv[3]);
	philo->time_to_sleep = ft_atol(argv[4]);
}