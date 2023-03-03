#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		*thread;
	int				count;
	int				i;
	pthread_mutex_t *mutex;
	void 			*retval;
}				t_philo;

void	error_exit(char *message, int status);

#endif