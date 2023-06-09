#include "philo.h"

bool	is_dead(t_philo *philo)
{
	if (philo->state == DIED)
		return (true);
	return (false);
}
