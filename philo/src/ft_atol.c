/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihashimo <ihashimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:33:19 by ihashimo          #+#    #+#             */
/*   Updated: 2023/07/11 11:33:19 by ihashimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	overflow(long num, const char *nptr, size_t i, int sign)
{
	long	n;

	n = nptr[i] - 48;
	if (sign == -1 && sign * num > (LONG_MAX - n) / 10)
		return (-1);
	if (sign == 1 && sign * num < (LONG_MIN + n) / 10)
		return (0);
	else
		return (1);
}

long	ft_atol(const char *nptr)
{
	size_t	i;
	long	sign;
	long	num;

	i = 0;
	num = 0;
	sign = -1;
	while (nptr[i] == ' ' || ('\t' <= nptr[i] && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		sign = sign * (44 - nptr[i]);
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		if (overflow(num, nptr, i, sign) != 1)
			return (overflow(num, nptr, i, sign));
		num = num * 10 - (nptr[i] - 48);
		i++;
	}
	return (sign * num);
}
