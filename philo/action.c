#include "philo.h"

void	philo_take_a_fork(t_philo *philo)
{
	(void)philo;
	printf("has taken a fork\n");
}

void	philo_eat(t_philo *philo)
{
	(void)philo;
	printf("is eating\n");
}

void	philo_sleep(t_philo *philo)
{
	(void)philo;
	printf("is sleeping\n");
}

void	philo_think(t_philo *philo)
{
	(void)philo;
	printf("is thinking\n");
}

void	*philo_actions(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// wait_start_time(philo->simulation->start);
	philo_think(philo);
	// while (is_dead(philo))
	// {

	// }
	return (NULL);
}
