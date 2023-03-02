#include "philo.h"

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	error_exit(char *message, int status)
{
	write(1, message, ft_strlen(message));
	exit(status);
}
