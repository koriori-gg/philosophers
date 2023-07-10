#include "philo.h"

bool	is_number(char *nptr)
{
	size_t	i;

	i = 0;
	while (nptr[i] == ' ' || ('\t' <= nptr[i] && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i])
	{
		if (!ft_isdigit(nptr[i]))
			return (false);
		i++;
	}
	return (true);
}
