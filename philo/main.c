#include "philo.h"

bool	is_valid(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	return (true);
}


void	start_simulation(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->num_philo)
	{
		pthread_create(&simulation->philo[i].thread, NULL, philo_actions, &(simulation->philo[i]));
		i++;
    }
}

void	stop_simulation(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->num_philo)
	{
		pthread_mutex_destroy(&(simulation->philo[i].l_fork));
		pthread_join(simulation->philo[i].thread, NULL);
		i++;
    }
}

int main(int argc, char **argv)
{
	t_simulation	simulation;

	if (argc != 5 && argc != 6)
	{
		printf("usage: ./philo num_philo die eat sleep\n");
		return (1);
	}
	if (!is_valid(argc, argv))
		return (1);
	init_simulation(argc, argv, &simulation);
	start_simulation(&simulation);
	stop_simulation(&simulation);
	return (0);
}
