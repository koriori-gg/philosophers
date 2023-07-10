#include "philo.h"

void	change_state(t_philo *philo, int state)
{
	philo->state = state;
}

void	add_eat_count(t_philo *philo)
{
	philo->eat_count += 1;
}

void	update_last_eat_time(t_philo *philo, long now)
{
	philo->last_eat_time = now;
}

void	update_stop(t_philo *philo)
{
	pthread_mutex_lock(&(philo->simulation->stop_mutex));
	philo->simulation->stop = true;
	pthread_mutex_unlock(&(philo->simulation->stop_mutex));
}

void	set_next_eat_time(t_philo *philo)
{
	if (philo->simulation->num_philo % 2 == 0)
		philo->next_eat_time = get_time() + philo->simulation->time_to_eat;
	else if (philo->simulation->num_philo == 3)
		philo->next_eat_time = get_time() + philo->simulation->time_to_eat * 2;
	else if (philo->simulation->num_philo == 3)
		philo->next_eat_time = get_time() + philo->simulation->time_to_eat * 3 / 2;
	else
		philo->next_eat_time = get_time() + calculate_next_eat_in_odd(philo);
}
