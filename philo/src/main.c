/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:33:37 by ihashimo          #+#    #+#             */
/*   Updated: 2023/07/11 11:33:38 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	simulation;

	if (!is_valid_argument(argc, argv))
		return (1);
	if (init_simulation(argc, argv, &simulation) != 0)
		return (1);
	if (start_simulation(&simulation) != 0)
		return (1);
	if (stop_simulation(&simulation, simulation.num_philo) != 0)
		return (1);
	return (0);
}
