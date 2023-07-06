#include "philo.h"

int	philo_eat(t_philo *philo)
{
	int		error;

	error = philo_take_fork(philo);
	if (error == 0)
	{
		change_state(philo, EAT);
		pthread_mutex_lock(&(philo->philo_mutex));
		error = print_action(philo, "is eating");
		update_last_eat_time(philo, philo->now);
		add_eat_count(philo);
		pthread_mutex_unlock(&(philo->philo_mutex));
		if (error == 0)
			wait_time(philo->now, philo->simulation->time_to_eat);
		set_next_eat_time(philo);
	}
	put_down_fork(&(philo->l_fork), philo->r_fork);
	return (error);
}

int	philo_sleep(t_philo *philo)
{
	int		error;

	change_state(philo, SLEEP);
	error = print_action(philo, "is sleeping");
	if (error == 0)
		wait_time(philo->now, philo->simulation->time_to_sleep);
	return (error);
}

int	philo_think(t_philo *philo)
{
	int		error;

	change_state(philo, THINK);
	error = print_action(philo, "is thinking");
	if (error == 0)
		wait_time(philo->now, philo->next_eat_time - philo->now);
	if (philo->id == 1 && philo->simulation->num_philo == 1 && philo->one_philo)
		wait_time(philo->now, philo->simulation->time_to_die);
	return (error);
}
