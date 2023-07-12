/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:34:00 by ihashimo          #+#    #+#             */
/*   Updated: 2023/07/12 18:48:24 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_max(long a, long b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

void	change_state(t_philo *philo, int state)
{
	philo->state = state;
}

void	set_next_eat_time(t_philo *philo)
{
	if (philo->simulation->num_philo % 2 == 0)
		philo->next_eat_time = philo->ideal_time
			+ ft_max(philo->simulation->time_to_eat,
				philo->simulation->time_to_sleep);
	else if (philo->simulation->num_philo == 3)
		philo->next_eat_time = philo->ideal_time
			+ ft_max(philo->simulation->time_to_eat * 2,
				philo->simulation->time_to_sleep);
	else if (philo->simulation->num_philo == 5)
		philo->next_eat_time = philo->ideal_time
			+ ft_max(philo->simulation->time_to_eat * 3 / 2,
				philo->simulation->time_to_sleep);
	else
		philo->next_eat_time = philo->ideal_time
			+ ft_max(calculate_next_eat_in_odd(philo),
				philo->simulation->time_to_sleep);
}
