#include "philo.h"

void	philo_eat(t_philo *philo)
{
	long	now;

	if (!is_same_state(philo, READY))
		return ;
	change_state(philo, EAT);
	// printf("id: %ld A\n", philo->id);
	now = get_time();
	update_last_eat_time(philo, now);
	// printf("id: %ld B\n", philo->id);
	if (!print_message(philo, now))
	{
		put_down_fork(&(philo->l_fork), philo->r_fork);
		return ;
	}
	// printf("id: %ld C\n", philo->id);
	add_eat_count(philo);
	// printf("id: %ld D\n", philo->id);
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
	// printf("id: %ld D\n", philo->id);
	now = get_time();
	// printf("id: %ld E\n", philo->id);
	if (!print_message(philo, now))
		return ;
	// printf("id: %ld F\n", philo->id);
	wait_time(now, philo->simulation->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	long	now;

	if (is_same_state(philo, THINK))
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
