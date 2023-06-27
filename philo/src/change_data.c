#include "philo.h"

void	change_state(t_philo *philo, int state)
{
	if (state == MIDDLE)
		philo->state = WAIT;
	else
		philo->state = state;
	if (state == EAT)
		philo->last_eat_time = get_time();
}

void	add_eat_count(t_philo *philo)
{
	pthread_mutex_lock(&(philo->simulation->mutex));
	philo->eat_count += 1;
	pthread_mutex_unlock(&(philo->simulation->mutex));
}

bool	update_philo(t_philo *philo, int state, long time)
{
	bool	flg;

	pthread_mutex_lock(&(philo->simulation->mutex));
	change_state(philo, state);
	flg = print_message(philo, time);
	pthread_mutex_unlock(&(philo->simulation->mutex));
	return (flg);
}