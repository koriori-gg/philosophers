#include "philo.h"

bool	is_valid(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	return (true);
}

void	monitor(t_simulation *simulation)
{
	long	i;
	long	now;

	i = 0;
	wait_start_time(simulation->start);
	while (1)
	{
		now = get_time();
			//mutex 必要かも
		if (now - simulation->philo[i].last_eat_time >= simulation->time_to_die)
		{
			simulation->philo[i].state = DIED;
			print_message(&(simulation->philo[i]), now);
			break ;
		}
		i++;
		if (simulation->num_philo == i)
			i = 0;
	}

}

void	start_simulation(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->num_philo)
	{
		pthread_create(&simulation->philo[i].thread, NULL, philo_actions, &(simulation->philo[i]));
		i++;
    }
	monitor(simulation);
}

void	stop_simulation(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->num_philo)
	{
		pthread_mutex_destroy(&(simulation->philo[i].l_fork));
		pthread_join(simulation->philo[i].thread, NULL);
		i++;
    }
}

int main(int argc, char **argv)
{
	t_simulation	simulation;

	if (argc != 5 && argc != 6)
	{
		printf("usage: ./philo num_philo die eat sleep\n");
		return (1);
	}
	if (!is_valid(argc, argv))
		return (1);
	init_simulation(argc, argv, &simulation);
	start_simulation(&simulation);
	stop_simulation(&simulation);
	return (0);
}
