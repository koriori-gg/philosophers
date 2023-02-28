#include "philo.h"

void *philo(void *arg)
{
	printf("I am Philo\n");
	printf("%s: %p\n", __func__, pthread_self());
	sleep(1);
	return (arg);
}

void eating(int time)
{
	usleep(time * 1000);
}

void sleeping(int time)
{
	usleep(time * 1000);
}

void thinking(int time)
{
	usleep(time * 1000);
}

//number_of_philosophers time_to_die time_to_eat time_to_sleep
int main(int argc, char **argv)
{
	pthread_t	*thread;
	int			count;
	int			i;
	void 		*retval;

   // スレッドを作成
   if (argc != 5)
		printf("argument error");
   	count = atoi(argv[1]);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * count);
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
