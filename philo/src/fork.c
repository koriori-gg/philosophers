#include "philo.h"

void	put_down_fork(pthread_mutex_t *fork_a, pthread_mutex_t *fork_b)
{
	if (fork_b == NULL)
		pthread_mutex_unlock(fork_a);
	else
	{
		pthread_mutex_unlock(fork_a);
		pthread_mutex_unlock(fork_b);
	}
}

void	pick_up_fork(t_philo *philo,
	pthread_mutex_t *fork_a, pthread_mutex_t *fork_b)
{
	pthread_mutex_lock(fork_a);
	if (!print_message(philo, get_time()))
	{
		put_down_fork(fork_a, NULL);
		return ;
	}
	if (philo->id == 1 && philo->simulation->num_philo == 1)
	{
		put_down_fork(fork_a, NULL);
		return ;
	}
	pthread_mutex_lock(fork_b);
	change_state(philo, READY);
	if (!print_message(philo, get_time()))
	{
		put_down_fork(fork_a, fork_b);
		return ;
	}
}

void	philo_take_fork(t_philo *philo)
{
	change_state(philo, WAIT);
	if (philo->id % 2 == 1)
		pick_up_fork(philo, &(philo->l_fork), philo->r_fork);
	else
		pick_up_fork(philo, philo->r_fork, &(philo->l_fork));
	if (philo->id == 1 && philo->simulation->num_philo == 1)
		philo->one_philo = true;
}
