/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:32:55 by ihashimo          #+#    #+#             */
/*   Updated: 2023/07/11 13:41:05 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	wait_time(long start, long time)
{
	long	remain;
	long	now;

	remain = time * 1000;
	while (remain > 0)
	{
		usleep((useconds_t)(remain / 2));
		now = get_time();
		remain = (start + time - now) * 1000;
	}
}

void	ideal_wait_time(t_philo *philo, int state)
{
	long	dt;

	if (state == THINK)
	{
		dt = philo->ideal_time - philo->now;
		wait_time(philo->now, philo->next_eat_time - philo->now + dt);
		philo->ideal_time = philo->next_eat_time;
	}
	if (state == EAT)
	{
		dt = philo->ideal_time - philo->now;
		wait_time(philo->now, philo->simulation->time_to_eat + dt);
		philo->ideal_time += philo->simulation->time_to_eat;
	}
	if (state == SLEEP)
	{
		dt = philo->ideal_time - philo->now;
		wait_time(philo->now, philo->simulation->time_to_sleep + dt);
		philo->ideal_time += philo->simulation->time_to_sleep;
	}
}

long	calculate_next_eat_in_odd(t_philo *philo)
{
	t_simulation	*sim;

	sim = philo->simulation;
	if (philo->id == 1 || philo->id == sim->num_philo
		|| philo->id == sim->num_philo - 1)
	{
		if (philo->eat_count % (sim->num_philo / 2) == 0
			|| philo->eat_count % (sim->num_philo / 2) == 1)
			return (sim->time_to_eat * 3 / 2);
		return (sim->time_to_eat);
	}
	if (philo->id == sim->num_philo - 2
		|| philo->id == sim->num_philo - 3)
	{
		if (philo->eat_count == 1)
			return (sim->time_to_eat * 3 / 2);
		if (philo->eat_count % (sim->num_philo / 2) == 1
			|| philo->eat_count % (sim->num_philo / 2) == 2)
			return (sim->time_to_eat * 3 / 2);
		return (sim->time_to_eat);
	}
	if ((philo->eat_count + (philo->id / 2)) % (sim->num_philo / 2) == 0
		|| (philo->eat_count + (philo->id / 2)) % (sim->num_philo / 2) == 1)
		return (sim->time_to_eat * 3 / 2);
	return (sim->time_to_eat);
}
