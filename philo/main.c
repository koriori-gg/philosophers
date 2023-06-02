#include "philo.h"

int main(int argc, char **argv)
{
	t_philo	philo;

	if (argc != 5)
	{
		printf("usage: ./philo num_philo die eat sleep\n");
		return (1);
	}
	init_philo(argc, argv, &philo);
	printf("%d\n", philo.number_of_philosophers);
}