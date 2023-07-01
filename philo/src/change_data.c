#include "philo.h"

void	change_state(t_philo *philo, int state)
{
	pthread_mutex_lock(&(philo->simulation->state_mutex));
	philo->state = state;
	pthread_mutex_unlock(&(philo->simulation->state_mutex));
}

void	add_eat_count(t_philo *philo)
{
	pthread_mutex_lock(&(philo->simulation->eat_count_mutex));
	philo->eat_count += 1;
	pthread_mutex_unlock(&(philo->simulation->eat_count_mutex));
}

void	update_last_eat_time(t_philo *philo)
{
	pthread_mutex_lock(&(philo->simulation->last_eat_mutex));
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&(philo->simulation->last_eat_mutex));
}

void	update_stop(t_philo *philo)
{
	if (philo->state != DIED)
		return ;
	pthread_mutex_lock(&(philo->simulation->dead_mutex));
	philo->simulation->stop = true;
	pthread_mutex_unlock(&(philo->simulation->dead_mutex));
}
