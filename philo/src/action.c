#include "philo.h"

void	philo_eat(t_philo *philo)
{
	long	now;

	if (!is_same_state(philo, READY))
		return ;
	now = get_time();
	pthread_mutex_lock(&(philo->philo_mutex));
	change_state(philo, EAT);
	update_last_eat_time(philo, now);
	if (!print_message(philo, philo->id, now, "is eating"))
	{
		put_down_fork(&(philo->l_fork), philo->r_fork);
		return ;
	}
	add_eat_count(philo);
	pthread_mutex_unlock(&(philo->philo_mutex));
	wait_time(now, philo->simulation->time_to_eat);
	set_next_eat_time(philo);
	put_down_fork(&(philo->l_fork), philo->r_fork);
}

void	philo_sleep(t_philo *philo)
{
	long	now;

	if (!is_same_state(philo, EAT))
		return ;
	pthread_mutex_lock(&(philo->philo_mutex));
	change_state(philo, SLEEP);
	now = get_time();
	if (!print_message(philo, philo->id, now, "is sleeping"))
		return ;
	pthread_mutex_unlock(&(philo->philo_mutex));
	wait_time(now, philo->simulation->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	long	now;

	if (is_same_state(philo, THINK))
		return ;
	now = get_time();
	pthread_mutex_lock(&(philo->philo_mutex));
	change_state(philo, THINK);
	if (!print_message(philo, philo->id, now, "is thinking"))
		return ;
	pthread_mutex_unlock(&(philo->philo_mutex));
	wait_time(now, philo->next_eat_time - now);
	if (philo->id == 1 && philo->simulation->num_philo == 1 && philo->one_philo)
		wait_time(now, philo->simulation->time_to_die);
}
