#include "philo.h"

void *philo(void *arg)
{
	printf("I am Philo\n");
	printf("%s: %p\n", __func__, pthread_self());
	printf("%p\n", arg);
	sleep(1);
	return (arg);
}

//usleep μs -> x100 = ms

void	take_a_fork()
{
	printf(" has taken a fork\n");
}
void eating(int time)
{
	printf(" is eating\n");
	usleep(time * 1000);
}

void sleeping(int time)
{
	printf(" is sleeping\n");
	usleep(time * 1000);
}

void thinking()
{
	printf(" is thinking\n");
}
//現在のphilo毎の状態を保存しておくものが必要そう<-じゃないと何回もthinkしたりしそう
//number_of_philosophers time_to_die time_to_eat time_to_sleep
int main(int argc, char **argv)
{
	pthread_t	*thread;
	int			count;
	int			i;
	pthread_mutex_t *mutex;
	void 		*retval;

	// スレッドを作成
	if (argc != 5)
		error_exit("argument error\n", EXIT_FAILURE);
	count = atoi(argv[1]);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * count);
	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * count);
	i = 0;
	while(i < count)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	i = 0;
	while(i < count)
	{
		if (pthread_create(&thread[i], NULL, philo, NULL) != 0)
			// エラー処理
			return (0);
		i++;
	}
	// スレッドの終了方法
	// 1. スレッドが終了するまで待つ
	i = 0;
	while(i < count)
	{
		pthread_join(thread[i], &retval);
		i++;
	}
	// 2. スレッドを待たない
	i = 0;
	while(i < count)
	{
		pthread_detach(thread[i]);
		i++;
	}
}
