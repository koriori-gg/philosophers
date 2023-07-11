/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:32:53 by ihashimo          #+#    #+#             */
/*   Updated: 2023/07/11 11:32:54 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_valid_argument(int argc, char **argv)
{
	int		i;
	long	num;

	if (argc != 5 && argc != 6)
	{
		printf("usage: ./philo num_philo die eat sleep\n");
		return (false);
	}
	if (ft_atol(argv[1]) == 0)
		return (false);
	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
			return (false);
		num = ft_atol(argv[i]);
		if ((num == 0 || num == -1) && ft_strlen(argv[i]) > 2)
			return (false);
		if (num <= 0 || num > INT_MAX)
			return (false);
		i++;
	}
	return (true);
}

bool	is_same_state(t_philo *philo, int state)
{
	if (philo->state == state)
		return (true);
	return (false);
}
