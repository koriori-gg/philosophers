#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	simulation;

	if (!is_valid_argument(argc, argv))
		return (1);
	if (init_simulation(argc, argv, &simulation) == -1)
		return (1);
	if (start_simulation(&simulation) == -1)
		return (1);
	if (stop_simulation(&simulation, simulation.num_philo))
		return (1);
	return (0);
}
