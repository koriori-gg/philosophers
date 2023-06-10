#include "philo.h"

void	philo_take_a_fork(t_philo *philo)
{
	philo->state = TAKE_A_FORK;
	pthread_mutex_lock(&(philo->l_fork));
	pthread_mutex_lock(philo->r_fork);
	printf("%ld %ld has taken a fork\n", get_time(), philo->id);//多分startとの差分の方がいい

}

void	philo_eat(t_philo *philo)
{
	philo->state = EAT;
	philo->last_eat_time = get_time();
	printf("%ld %ld is eating\n", philo->last_eat_time, philo->id);
	wait_time(philo->last_eat_time, philo->simulation->time_to_eat);
	pthread_mutex_unlock(&(philo->l_fork));
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleep(t_philo *philo)
{
	long now;

	philo->state = SLEEP;
	now = get_time();
	printf("%ld %ld is sleeping\n", now, philo->id);
	wait_time(now, philo->simulation->time_to_eat);
}

void	philo_think(t_philo *philo)
{
	philo->state = THINK;
	printf("is thinking\n");
}

void	*philo_actions(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_start_time(philo->simulation->start);
	if (philo->id % 2 == 1)
	{
		wait_time(philo->simulation->start, philo->simulation->time_to_eat);
	}
	while (!is_dead(philo))
	{
		philo_take_a_fork(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
