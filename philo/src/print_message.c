/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:33:41 by ihashimo          #+#    #+#             */
/*   Updated: 2023/07/11 11:33:42 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_dead(long time, long id, char *message)
{
	printf("%ld %ld %s\n", time, id, message);
}

int	update_philo(t_philo *philo, char *message, int state)
{
	long	time;
	int		stop;

	pthread_mutex_lock(&(philo->simulation->monitor->stop_mutex));
	stop = 0;
	philo->now = get_time();
	time = philo->ideal_time - philo->simulation->start;
	if (philo->simulation->monitor->stop)
		stop = -1;
	if (stop == 0)
		printf("%ld %ld %s\n", time, philo->id, message);
	if (state == EAT)
	{
		philo->last_eat_time = philo->now;
		philo->eat_count += 1;
	}
	pthread_mutex_unlock(&(philo->simulation->monitor->stop_mutex));
	return (stop);
}
