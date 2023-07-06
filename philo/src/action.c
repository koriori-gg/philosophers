#include "philo.h"

int	philo_eat(t_philo *philo)
{
	long	now;

	if (philo_take_fork(philo) == -1)
		return (-1);
	now = get_time();
	pthread_mutex_lock(&(philo->philo_mutex));
	change_state(philo, EAT);
	update_last_eat_time(philo, now);
	print_message(philo, philo->id, now, "is eating");
	add_eat_count(philo);
	pthread_mutex_unlock(&(philo->philo_mutex));
	wait_time(now, philo->simulation->time_to_eat);
	set_next_eat_time(philo);
	put_down_fork(&(philo->l_fork), philo->r_fork);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	long	now;

	if (should_stop(philo))
		return (-1);
	pthread_mutex_lock(&(philo->philo_mutex));
	change_state(philo, SLEEP);
	now = get_time();
	print_message(philo, philo->id, now, "is sleeping");
	pthread_mutex_unlock(&(philo->philo_mutex));
	wait_time(now, philo->simulation->time_to_sleep);
	return (0);
}

int	philo_think(t_philo *philo)
{
	long	now;

	if (should_stop(philo))
		return (-1);
	now = get_time();
	pthread_mutex_lock(&(philo->philo_mutex));
	change_state(philo, THINK);
	print_message(philo, philo->id, now, "is thinking");
	pthread_mutex_unlock(&(philo->philo_mutex));
	wait_time(now, philo->next_eat_time - now);
	if (philo->id == 1 && philo->simulation->num_philo == 1 && philo->one_philo)
		wait_time(now, philo->simulation->time_to_die);
	return (0);
}
