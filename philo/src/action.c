#include "philo.h"

void	philo_eat(t_philo *philo)
{
	long	now;

	if (!is_same_state(philo, READY))
		return ;
	change_state(philo, EAT);
	now = get_time();
	update_last_eat_time(philo, now);
	if (!print_message(philo, philo->id, now, "is eating"))
	{
		put_down_fork(&(philo->l_fork), philo->r_fork);
		return ;
	}
	add_eat_count(philo);
	wait_time(now, philo->simulation->time_to_eat);
	put_down_fork(&(philo->l_fork), philo->r_fork);
	set_next_eat_time(philo);
}

void	philo_sleep(t_philo *philo)
{
	long	now;

	if (!is_same_state(philo, EAT))
		return ;
	change_state(philo, SLEEP);
	now = get_time();
	if (!print_message(philo, philo->id, now, "is sleeping"))
		return ;
	wait_time(now, philo->simulation->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	long	now;

	if (is_same_state(philo, THINK))
		return ;
	now = get_time();
	change_state(philo, THINK);
	if (!print_message(philo, philo->id, now, "is thinking"))
		return ;
	wait_time(now, philo->next_eat_time - now);
	if (philo->id == 1 && philo->simulation->num_philo == 1 && philo->one_philo)
		wait_time(now, philo->simulation->time_to_die);
}
