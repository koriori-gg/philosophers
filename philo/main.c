#include "philo.h"

void *philosopher(void *philo)
{
	printf("I am Philo\n");
	printf("%s: %p\n", __func__, pthread_self());
	printf("%d\n", ((t_philo *)philo)->i);
	sleep(1);
	return (philo);
}

//現在のphilo毎の状態を保存しておくものが必要そう<-じゃないと何回もthinkしたりしそう
//number_of_philosophers time_to_die time_to_eat time_to_sleep
int main(int argc, char **argv)
{
	t_philo	philo;

	// スレッドを作成
	if (argc != 5)
		error_exit("argument error\n", EXIT_FAILURE);
	philo.count = atoi(argv[1]);
	philo.thread = (pthread_t *)malloc(sizeof(pthread_t) * philo.count);
	philo.mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo.count);
	philo.i = 0;
	while(philo.i < philo.count)
	{
		pthread_mutex_init(&philo.mutex[philo.i], NULL);
		philo.i++;
	}
	philo.i = 0;
	while(philo.i < philo.count)
	{
		if (pthread_create(&philo.thread[philo.i], NULL, philosopher, &philo) != 0)
			// エラー処理
			return (0);
		philo.i++;
	}
	// スレッドの終了方法
	// 1. スレッドが終了するまで待つ
	philo.i = 0;
	while(philo.i < philo.count)
	{
		pthread_join(philo.thread[philo.i], &philo.retval);
		philo.i++;
	}
	// 2. スレッドを待たない
	philo.i = 0;
	while(philo.i < philo.count)
	{
		pthread_detach(philo.thread[philo.i]);
		philo.i++;
	}
}
