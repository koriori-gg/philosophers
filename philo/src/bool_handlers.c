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

bool	is_dead(t_philo *philo)
{
	if (philo->simulation->stop)
		return (true);
	return (false);
}

bool	has_finished_eat(t_philo *philo)
{
	t_simulation	*simulation;
	int				i;

	simulation = philo->simulation;
	if (simulation->must_eat == -1)
		return (false);
	i = 0;
	while (i < simulation->num_philo)
	{
		if (simulation->philo[i].eat_count < simulation->must_eat)
			return (false);
		i++;
	}
	ft_pthread_mutex_lock(&(simulation->mutex));
	simulation->stop = true;
	ft_pthread_mutex_unlock(&(simulation->mutex));
	return (true);
}
