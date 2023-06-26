#include "philo.h"

void	philo_eat(t_philo *philo)
{
	if (philo->state != READY)
		return ;
	if (!update_philo(philo, EAT, philo->last_eat_time))
	{
		put_down_fork(&(philo->l_fork), philo->r_fork);
		return ;
	}
	wait_time(philo->last_eat_time, philo->simulation->time_to_eat);
	add_eat_count(philo);
	put_down_fork(&(philo->l_fork), philo->r_fork);
}

void	philo_sleep(t_philo *philo)
{
	long	now;

	if (philo->state != EAT)
		return ;
	now = get_time();
	if (!update_philo(philo, SLEEP, now))
		return ;
	wait_time(now, philo->simulation->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	long	now;

	now = get_time();
	if (philo->state == THINK)
		return ;
	if (!update_philo(philo, THINK, now))
		return ;
	if (philo->id == 1 && philo->simulation->num_philo == 1)
		wait_time(now, philo->simulation->time_to_die * 2);
}
