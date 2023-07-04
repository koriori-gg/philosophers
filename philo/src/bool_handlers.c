#include "philo.h"

bool	is_valid_argument(int argc, char **argv)
{
	int		i;
	long	num;

	if (argc != 5 && argc != 6)
	{
		printf("usage: ./philo num_philo die eat sleep\n");
		return (false);
	}
	if (ft_atol(argv[1]) == 0)
		return (false);
	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
			return (false);
		num = ft_atol(argv[i]);
		if ((num == 0 || num == -1) && ft_strlen(argv[i]) > 2)
			return (false);
		if (num <= 0 || num > INT_MAX)
			return (false);
		i++;
	}
	return (true);
}

bool	should_stop(t_philo *philo)
{
	bool	flg;

	flg = false;
	pthread_mutex_lock(&(philo->simulation->stop_mutex));
	if (philo->simulation->stop)
		flg = true;
	pthread_mutex_unlock(&(philo->simulation->stop_mutex));
	return (flg);
}

bool	has_finished_eat(t_simulation *simulation)
{
	int	i;

	if (simulation->must_eat == -1)
		return (false);
	i = 0;
	pthread_mutex_lock(&(simulation->eat_count_mutex));
	while (i < simulation->num_philo)
	{
		if (simulation->philo[i].eat_count < simulation->must_eat)
		{
			pthread_mutex_unlock(&(simulation->eat_count_mutex));
			return (false);
		}
		i++;
	}
	pthread_mutex_unlock(&(simulation->eat_count_mutex));
	pthread_mutex_lock(&(simulation->stop_mutex));
	simulation->stop = true;
	pthread_mutex_unlock(&(simulation->stop_mutex));
	return (true);
}

bool	is_same_state(t_philo *philo, int state)
{
	pthread_mutex_lock(&(philo->simulation->state_mutex));
	if (philo->state == state)
	{
		pthread_mutex_unlock(&(philo->simulation->state_mutex));
		return (true);
	}
	pthread_mutex_unlock(&(philo->simulation->state_mutex));
	return (false);
}
