#include "philo.h"

bool	is_valid_argument(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("usage: ./philo num_philo die eat sleep\n");
		return (false);
	}
	if (ft_atol(argv[0]) == 0)
		return (false);
	i = 1;
	while (i < argc)
	{
		if ((ft_atol(argv[i]) == 0 || ft_atol(argv[i]) == -1) && ft_strlen(argv[i]) > 2)
			return (false);
	}
	return (true);
}

bool	is_dead(t_philo *philo)
{
	if (philo->state == DIED)
		return (true);
	return (false);
}
