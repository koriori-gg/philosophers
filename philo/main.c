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

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	error_exit(char *message, int status)
{
	write(1, message, ft_strlen(message));
	exit(status);
}

//number_of_philosophers time_to_die time_to_eat time_to_sleep
int main(int argc, char **argv)
{
	pthread_t	*thread;
	int			count;
	int			i;
	pthread_mutex_t mutex;
	void 		*retval;

	// スレッドを作成
	if (argc != 5)
		error_exit("argument error\n", EXIT_FAILURE);
	count = atoi(argv[1]);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * count);
	pthread_mutex_init(&mutex, NULL);
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
