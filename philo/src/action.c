#include "philo.h"

void	pick_up_fork(t_philo *philo,
	pthread_mutex_t *fork_a, pthread_mutex_t *fork_b)
{
	ft_pthread_mutex_lock(fork_a);
	if (!print_message(philo, get_time()))
	{
		ft_pthread_mutex_unlock(fork_a);
		return ;
	}
	if (philo->id == 1 && philo->simulation->num_philo == 1)
	{
		ft_pthread_mutex_unlock(fork_a);
		return ;
	}
	ft_pthread_mutex_lock(fork_b);
	if (!print_message(philo, get_time()))
	{
		ft_pthread_mutex_unlock(fork_a);
		ft_pthread_mutex_unlock(fork_b);
		return ;
	}
	philo->state = READY;
}

void	philo_take_fork(t_philo *philo)
{
	philo->state = WAIT;
	if (philo->id % 2 == 1)
		pick_up_fork(philo, &(philo->l_fork), philo->r_fork);
	else
		pick_up_fork(philo, philo->r_fork, &(philo->l_fork));
}

void	philo_eat(t_philo *philo)
{
	if (philo->state != READY)
		return ;
	philo->state = EAT;
	philo->last_eat_time = get_time();
	if (!print_message(philo, philo->last_eat_time))
	{
		ft_pthread_mutex_unlock(&(philo->l_fork));
		ft_pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	wait_time(philo->last_eat_time, philo->simulation->time_to_eat);
	philo->eat_count += 1;
	ft_pthread_mutex_unlock(&(philo->l_fork));
	ft_pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleep(t_philo *philo)
{
	long	now;

	if (philo->state != EAT)
		return ;
	philo->state = SLEEP;
	now = get_time();
	if (!print_message(philo, now))
		return ;
	wait_time(now, philo->simulation->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	long	now;

	now = get_time();
	if (philo->state == THINK)
		return ;
	philo->state = THINK;
	if (!print_message(philo, now))
		return ;
	if (philo->id == 1 && philo->simulation->num_philo == 1)
		wait_time(now, philo->simulation->time_to_die * 2);
}
