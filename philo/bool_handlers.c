#include "philo.h"

bool	is_valid(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	return (true);
}

bool	is_dead(t_philo *philo)
{
	if (philo->state == DIED)
		return (true);
	return (false);
}
