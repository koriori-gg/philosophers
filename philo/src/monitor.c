/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:33:07 by ihashimo          #+#    #+#             */
/*   Updated: 2023/07/11 14:41:32 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	stop_philo(t_simulation *simulation, int i)
{
	pthread_mutex_lock(&(simulation->monitor->stop_mutex));
	if (i >= 0)
		print_dead(get_time() - simulation->start,
			simulation->philo[i].id, "is dead");
	simulation->monitor->stop = true;
	pthread_mutex_unlock(&(simulation->monitor->stop_mutex));
	return (false);
}

bool	check_philo(t_simulation *simulation)
{
	long	i;
	bool	need;
	long	now;
	long	eat_count;

	i = 0;
	need = true;
	eat_count = 0;
	while (i < simulation->num_philo && need)
	{
		pthread_mutex_lock(&(simulation->philo[i].philo_mutex));
		now = get_time();
		if (now - simulation->philo[i].last_eat_time >= simulation->time_to_die)
			need = stop_philo(simulation, i);
		if (simulation->philo[i].eat_count >= simulation->must_eat)
			eat_count += 1;
		pthread_mutex_unlock(&(simulation->philo[i].philo_mutex));
		i++;
	}
	if (simulation->must_eat != -1 && eat_count == simulation->num_philo)
		need = stop_philo(simulation, -1);
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
