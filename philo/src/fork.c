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

int	pick_up_fork(t_philo *philo,
	pthread_mutex_t *fork_a, pthread_mutex_t *fork_b)
{
	int	error;

	pthread_mutex_lock(fork_a);
	error = update_philo(philo, "has taken a fork", THINK);
	if (error == -1 || (philo->id == 1 && philo->simulation->num_philo == 1))
		put_down_fork(fork_a, NULL);
	else
	{
		pthread_mutex_lock(fork_b);
		error = update_philo(philo, "has taken a fork", THINK);
		if (error == -1)
			put_down_fork(fork_a, fork_b);
	}
	return (error);
}

int	philo_take_fork(t_philo *philo)
{
	int	error;

	if (philo->id % 2 == 1)
		error = pick_up_fork(philo, &(philo->l_fork), philo->r_fork);
	else
		error = pick_up_fork(philo, philo->r_fork, &(philo->l_fork));
	if (philo->id == 1 && philo->simulation->num_philo == 1)
		philo->one_philo = true;
	return (error);
}
