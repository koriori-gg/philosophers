#include "philo.h"

bool	print_message(t_philo *philo, long now)
{
	long	time;

	ft_pthread_mutex_lock(&(philo->simulation->mutex));
	if (philo->simulation->stop)
	{
		ft_pthread_mutex_unlock(&(philo->simulation->mutex));
		return (false);
	}
	time = now - philo->simulation->start;
	if (philo->state == TAKE_A_FORK)
		printf("%ld %ld has taken a fork\n", time, philo->id);
	if (philo->state == EAT)
		printf("%ld %ld is eating\n", time, philo->id);
	if (philo->state == SLEEP)
		printf("%ld %ld is sleeping\n", time, philo->id);
	if (philo->state == THINK)
		printf("%ld %ld is thinking\n", time, philo->id);
	if (philo->state == DIED)
		printf("%ld %ld is died\n", time, philo->id);
	ft_pthread_mutex_unlock(&(philo->simulation->mutex));
	return (true);
}

void	philo_take_a_fork(t_philo *philo)
{
	philo->state = TAKE_A_FORK;
	if (philo->id % 2 == 0)
	{
		ft_pthread_mutex_lock(&(philo->l_fork));
		if (!print_message(philo, get_time()))
		{
			ft_pthread_mutex_unlock(&(philo->l_fork));
			return ;
		}
		ft_pthread_mutex_lock(philo->r_fork);
		if (!print_message(philo, get_time()))
		{
			ft_pthread_mutex_unlock(&(philo->l_fork));
			ft_pthread_mutex_unlock(philo->r_fork);
			return ;
		}
	}
	else
	{
		ft_pthread_mutex_lock(philo->r_fork);
		if (!print_message(philo, get_time()))
		{
			ft_pthread_mutex_unlock(&(philo->l_fork));
			return ;
		}
		ft_pthread_mutex_lock(&(philo->l_fork));
		if (!print_message(philo, get_time()))
		{
			ft_pthread_mutex_unlock(philo->r_fork);
			ft_pthread_mutex_unlock(&(philo->l_fork));
			return ;
		}
	}
}

void	philo_eat(t_philo *philo)
{
	philo->state = EAT;
	philo->last_eat_time = get_time();
	if (!print_message(philo, philo->last_eat_time))
	{
		ft_pthread_mutex_unlock(&(philo->l_fork));
		ft_pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	wait_time(philo->last_eat_time, philo->simulation->time_to_eat);
	ft_pthread_mutex_unlock(&(philo->l_fork));
	ft_pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleep(t_philo *philo)
{
	long now;

	philo->state = SLEEP;
	now = get_time();
	if (!print_message(philo, now))
		return ;
	wait_time(now, philo->simulation->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	if (philo->state == THINK)
		return ;
	philo->state = THINK;
	if (!print_message(philo, get_time()))
		return ;
}

void	*philo_actions(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_start_time(philo->simulation->start);
	if (philo->id / 2 == 0)
		wait_time(philo->simulation->start, philo->simulation->time_to_eat / 2);
	while (!is_dead(philo))
	{
		philo_take_a_fork(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
