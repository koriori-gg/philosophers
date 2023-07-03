#include "philo.h"

void	philo_eat(t_philo *philo)
{
	if (philo->state != READY)
		return ;
	change_state(philo, EAT);
	update_last_eat_time(philo);
	if (!print_message(philo, philo->last_eat_time))
	{
		put_down_fork(&(philo->l_fork), philo->r_fork);
		return ;
	}
	wait_time(philo->last_eat_time, philo->simulation->time_to_eat);
	put_down_fork(&(philo->l_fork), philo->r_fork);
	add_eat_count(philo);
	set_next_eat_time(philo);
}

void	philo_sleep(t_philo *philo)
{
	long	now;

	if (philo->state != EAT)
		return ;
	change_state(philo, SLEEP);
	now = get_time();
	if (!print_message(philo, now))
		return ;
	wait_time(now, philo->simulation->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	long	now;

	if (philo->state == THINK)
		return ;
	now = get_time();
	if (philo->next_eat_time <= now)
		return ;
	change_state(philo, THINK);
	if (!print_message(philo, now))
		return ;
	wait_time(now, philo->next_eat_time - now);
	if (philo->id == 1 && philo->simulation->num_philo == 1)
		wait_time(now, philo->simulation->time_to_die * 2);
}
