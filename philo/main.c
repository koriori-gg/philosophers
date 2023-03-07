#include "philo.h"

void *philosopher(void *philo)
{
	printf("I am Philo\n");
	printf("%s: %p\n", __func__, pthread_self());
	printf("%d\n", ((t_philo *)philo)->i);
	sleep(1);
	while (1)
	{
		eating((t_philo *)philo);
		sleeping((t_philo *)philo);
		thinking((t_philo *)philo);
		printf("%d\n", ((t_philo *)philo)->i);
	}
	return (philo);
}

//現在のphilo毎の状態を保存しておくものが必要そう<-じゃないと何回もthinkしたりしそう
//number_of_philosophers time_to_die time_to_eat time_to_sleep
int main(int argc, char **argv)
{
	t_philo	philo;
	int		i;

	// スレッドを作成
	if (argc != 5)
		error_exit("argument error\n", EXIT_FAILURE);
	philo.count = atoi(argv[1]);
	philo.time_to_die = atoi(argv[2]);
	philo.time_to_eat = atoi(argv[3]);
	philo.time_to_sleep = atoi(argv[4]);
	philo.thread = (pthread_t *)malloc(sizeof(pthread_t) * philo.count);
	philo.fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo.count);
	i = 0;
	while(i < philo.count)
	{
		pthread_mutex_init(&philo.fork[i], NULL);
		i++;
	}
	i = 0;
	while(i < philo.count)
	{
		if (pthread_create(&philo.thread[i], NULL, philosopher, &philo) != 0)
			// エラー処理
			return (0);
		i++;
	}
	// スレッドの終了方法
	// 1. スレッドが終了するまで待つ
	i = 0;
	while(i < philo.count)
	{
		pthread_join(philo.thread[i], &philo.retval);
		i++;
	}
	// 2. スレッドを待たない
	i = 0;
	while(i < philo.count)
	{
		pthread_detach(philo.thread[i]);
		i++;
	}
}
