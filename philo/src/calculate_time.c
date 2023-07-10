#include "philo.h"

long	calculate_next_eat_in_odd(t_philo *philo)
{
	//pattern1
	if (philo->id == 1 || philo->id == philo->simulation->num_philo || philo->id == philo->simulation->num_philo - 1)
	{
		if (philo->eat_count % (philo->simulation->num_philo / 2) == 0 || philo->eat_count % (philo->simulation->num_philo / 2) == 1)
			return (philo->simulation->time_to_eat * 3 / 2);
		return (philo->simulation->time_to_eat);
	}
	//pattern2
	if (philo->id == philo->simulation->num_philo - 2 || philo->id == philo->simulation->num_philo - 3)
	{
		if (philo->eat_count == 1)
			return (philo->simulation->time_to_eat * 3 / 2);
		if (philo->eat_count % (philo->simulation->num_philo / 2) == 1 || philo->eat_count % (philo->simulation->num_philo / 2) == 2)
			return (philo->simulation->time_to_eat * 3 / 2);
		return (philo->simulation->time_to_eat);
	}
	//etc if pattern2の兼ねる
	if ((philo->eat_count + (philo->id / 2)) % (philo->simulation->num_philo / 2) == 0 || (philo->eat_count + (philo->id / 2)) % (philo->simulation->num_philo / 2) == 1)
		return (philo->simulation->time_to_eat * 3 / 2);
	return (philo->simulation->time_to_eat);
}
