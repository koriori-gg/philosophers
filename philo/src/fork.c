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
	pthread_mutex_lock(fork_a);
	print_message(philo, philo->id, get_time(), "has taken a fork");
	if (should_stop(philo))
	{
		put_down_fork(fork_a, NULL);
		return (-1);
	}
	if (philo->id == 1 && philo->simulation->num_philo == 1)
	{
		put_down_fork(fork_a, NULL);
		return (-1);
	}
	pthread_mutex_lock(fork_b);
	print_message(philo, philo->id, get_time(), "has taken a fork");
	if (should_stop(philo))
	{
		put_down_fork(fork_a, fork_b);
		return (-1);
	}
	return (0);
}

int	philo_take_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
		return (pick_up_fork(philo, &(philo->l_fork), philo->r_fork));
	else
		return (pick_up_fork(philo, philo->r_fork, &(philo->l_fork)));
	if (philo->id == 1 && philo->simulation->num_philo == 1)
		philo->one_philo = true;
	return (0);
}
