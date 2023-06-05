#include "philo.h"

long long sum = 0;

void *add(void *arg)
{
	(void)arg;
	sum += 1;
	return (NULL);
}
int main(int argc, char **argv)
{
	t_table	table;
	int		i;

	if (argc != 5)
	{
		printf("usage: ./philo num_philo die eat sleep\n");
		return (1);
	}
	init_table(argc, argv, &table);
	// init_philo(argc, argv, &philo);
	printf("%ld\n", table.num_philo);
	//スレッド開始
	i = 0;
	while (i < table.num_philo)
	{
        pthread_create(&table.philo[i].thread, NULL, add, &(table.philo[i]));
		i++;
    }
	// //終了待ち
	i = 0;
	while (i < table.num_philo)
	{
        pthread_join(table.philo[i].thread, NULL);
		i++;
    }
	return (0);
}
