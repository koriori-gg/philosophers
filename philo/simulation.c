#include "philo.h"

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
			simulation->stop = true;
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
		ft_pthread_create(&simulation->philo[i].thread, philo_actions, &(simulation->philo[i]));
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
		ft_pthread_mutex_destroy(&(simulation->philo[i].l_fork));
		ft_pthread_join(simulation->philo[i].thread);
		i++;
	}
	ft_pthread_mutex_destroy(&simulation->mutex);
}
