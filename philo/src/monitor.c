/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:33:07 by ihashimo          #+#    #+#             */
/*   Updated: 2023/07/11 11:33:08 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_philo(t_simulation *simulation)
{
	long	i;
	bool	need;
	long	now;

	i = 0;
	need = true;
	while (i < simulation->num_philo && need)
	{
		pthread_mutex_lock(&(simulation->philo[i].philo_mutex));
		now = get_time();
		if (now - simulation->philo[i].last_eat_time >= simulation->time_to_die)
		{
			pthread_mutex_lock(&(simulation->monitor->stop_mutex));
			print_dead(get_time() - simulation->start,
				simulation->philo[i].id, "is dead");
			simulation->monitor->stop = true;
			need = false;
			pthread_mutex_unlock(&(simulation->monitor->stop_mutex));
		}
		pthread_mutex_unlock(&(simulation->philo[i].philo_mutex));
		i++;
	}
	return (need);
}

void	*monitor(void *arg)
{
	t_simulation	*simulation;
	bool			need_to_continue;

	simulation = (t_simulation *)arg;
	need_to_continue = true;
	while (need_to_continue)
	{
		usleep(INTERVAL);
		need_to_continue = check_philo(simulation);
	}
	return (NULL);
}
