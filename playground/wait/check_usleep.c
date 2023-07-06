#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philo {
	long				id;
	long				start;
	pthread_t			thread;
}	t_philo;

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	wait_start_time(long start)
{
	long	remain;
	long	now;

	now = get_time();
	remain = start - now;
	while (remain > 0)
	{
		usleep((useconds_t)(remain / 2));
		now = get_time();
		remain = start - now;
	}
}

void	*test_sleep(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	wait_start_time(philo->start);
	usleep(200);
	printf("%ld %ld\n", philo->id, get_time() - philo->start);
	return (NULL);
}

void	init_philo(t_philo *philo ,long num)
{
	long		start;
	long		i;
	start = get_time() + 1000;
	i = 0;
	while (i < num)
	{
		philo->id = i;
		philo->start = start;
		i++;
	}
}

int main(void)
{
	t_philo		*philo;
	long		num;
	long		i;

	num = 30;
	philo = (t_philo *)malloc(sizeof(t_philo) * num);
	if (!philo)
		return (1);
	init_philo(philo, num);
	i = 0;
	while (i < num)
	{
		if(pthread_create(&philo[i].thread, NULL, test_sleep, &philo[i]) != 0)
		{
			printf("out\n");
			return (-1);
		}
		i++;
	}
}
