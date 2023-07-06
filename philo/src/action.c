#include "philo.h"

int	philo_eat(t_philo *philo)
{
	long	now;
	int		error;

	error = philo_take_fork(philo);
	if (error == 0)
	{
		now = get_time();
		change_state(philo, EAT);
		pthread_mutex_lock(&(philo->philo_mutex));
		update_last_eat_time(philo, now);
		error = print_action(philo, philo->id, now, "is eating");
		add_eat_count(philo);
		pthread_mutex_unlock(&(philo->philo_mutex));
		if (error == 0)
			wait_time(now, philo->simulation->time_to_eat);
		set_next_eat_time(philo);
	}
	put_down_fork(&(philo->l_fork), philo->r_fork);
	return (error);
}

int	philo_sleep(t_philo *philo)
{
	long	now;
	int		error;

	change_state(philo, SLEEP);
	now = get_time();
	error = print_action(philo, philo->id, now, "is sleeping");
	if (error == 0)
		wait_time(now, philo->simulation->time_to_sleep);
	return (error);
}

int	philo_think(t_philo *philo)
{
	long	now;
	int		error;

	now = get_time();
	change_state(philo, THINK);
	error = print_action(philo, philo->id, now, "is thinking");
	if (error == 0)
		wait_time(now, philo->next_eat_time - now);
	if (philo->id == 1 && philo->simulation->num_philo == 1 && philo->one_philo)
		wait_time(now, philo->simulation->time_to_die);
	return (error);
}
