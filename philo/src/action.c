#include "philo.h"

int	philo_eat(t_philo *philo)
{
	int		stop;

	stop = philo_take_fork(philo);
	if (stop == 0)
	{
		change_state(philo, EAT);
		pthread_mutex_lock(&(philo->philo_mutex));
		stop = update_philo(philo, "is eating", EAT);
		pthread_mutex_unlock(&(philo->philo_mutex));
		if (stop == 0)
			wait_time(philo->now, philo->simulation->time_to_eat);
		set_next_eat_time(philo);
	}
	put_down_fork(&(philo->l_fork), philo->r_fork);
	return (stop);
}

int	philo_sleep(t_philo *philo)
{
	int		stop;

	change_state(philo, SLEEP);
	stop = update_philo(philo, "is sleeping", SLEEP);
	if (stop == 0)
		wait_time(philo->now, philo->simulation->time_to_sleep);
	return (stop);
}

int	philo_think(t_philo *philo)
{
	int		stop;

	change_state(philo, THINK);
	stop = update_philo(philo, "is thinking", THINK);
	if (stop == 0)
		wait_time(philo->now, philo->next_eat_time - philo->now);
	if (philo->id == 1 && philo->simulation->num_philo == 1 && philo->one_philo)
		wait_time(philo->now, philo->simulation->time_to_die);
	return (stop);
}
