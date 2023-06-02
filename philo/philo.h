#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h> 

typedef struct s_philo {
	long number_of_philosophers;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
}	t_philo;

void	init_philo(int argc, char **argv, t_philo *philo);
long	ft_atol(const char *nptr);
int	    ft_isdigit(int d);
#endif