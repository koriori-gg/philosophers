/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:33:56 by ihashimo          #+#    #+#             */
/*   Updated: 2023/07/11 11:33:57 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
