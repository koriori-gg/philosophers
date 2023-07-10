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
	int	stop;

	pthread_mutex_lock(fork_a);
	stop = update_philo(philo, "has taken a fork", THINK);
	if (stop == -1 || (philo->id == 1 && philo->simulation->num_philo == 1))
		put_down_fork(fork_a, NULL);
	else
	{
		pthread_mutex_lock(fork_b);
		stop = update_philo(philo, "has taken a fork", THINK);
		if (stop == -1)
			put_down_fork(fork_a, fork_b);
	}
	return (stop);
}

int	philo_take_fork(t_philo *philo)
{
	int	stop;

	if (philo->id % 2 == 1)
		stop = pick_up_fork(philo, &(philo->l_fork), philo->r_fork);
	else
		stop = pick_up_fork(philo, philo->r_fork, &(philo->l_fork));
	if (philo->id == 1 && philo->simulation->num_philo == 1)
		philo->one_philo = true;
	return (stop);
}
