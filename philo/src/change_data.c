#include "philo.h"

void	change_state(t_philo *philo, int state)
{
	philo->state = state;
}

void	set_next_eat_time(t_philo *philo)
{
	if (philo->simulation->num_philo % 2 == 0)
		philo->next_eat_time = philo->ideal_time + philo->simulation->time_to_eat;
	else if (philo->simulation->num_philo == 3)
		philo->next_eat_time = philo->ideal_time + philo->simulation->time_to_eat * 2;
	else if (philo->simulation->num_philo == 3)
		philo->next_eat_time = philo->ideal_time + philo->simulation->time_to_eat * 3 / 2;
	else
		philo->next_eat_time = philo->ideal_time + calculate_next_eat_in_odd(philo);
}
