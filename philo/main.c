#include "philo.h"

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
