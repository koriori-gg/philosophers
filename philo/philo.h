#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_philo {
	pthread_t	thread;
}	t_philo;
typedef struct s_table {
	long		num_philo;
    long		time_to_die;
    long		time_to_eat;
    long		time_to_sleep;
	t_philo		*philo;
}	t_table;

void	init_table(int argc, char **argv, t_table *table);
long	ft_atol(const char *nptr);
int	    ft_isdigit(int d);
#endif