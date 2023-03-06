#include "philo.h"
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
