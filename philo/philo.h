#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_philo {
	int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
}	t_philo;

void	init_philo(int argc, char **argv, t_philo *philo);
#endif