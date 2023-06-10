#include "philo.h"

int main(int argc, char **argv)
{
	t_simulation	simulation;

	if (!is_valid(argc, argv))
		return (1);
	init_simulation(argc, argv, &simulation);
	start_simulation(&simulation);
	stop_simulation(&simulation);
	return (0);
}
