#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	simulation;

	if (!is_valid_argument(argc, argv))
		return (1);
	if (init_simulation(argc, argv, &simulation) != 0)
		return (1);
	// int i = 0;
	// while (i < simulation.num_philo)
	// 	printf("philo next %ld\n", simulation.philo[i++].next_eat_time);
	if (start_simulation(&simulation) != 0)
		return (1);
	if (stop_simulation(&simulation, simulation.num_philo) != 0)
		return (1);
	return (0);
}
