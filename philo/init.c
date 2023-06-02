#include "philo.h"

void	init_philo(int argc, char **argv, t_philo *philo)
{
	(void)argc;
	philo->number_of_philosophers = atoi(argv[1]);
	philo->time_to_die = atoi(argv[2]);
	philo->time_to_eat = atoi(argv[3]);
	philo->time_to_sleep = atoi(argv[4]);
}