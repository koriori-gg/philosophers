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
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				i;
	pthread_mutex_t *mutex;
	void 			*retval;
}				t_philo;

void	error_exit(char *message, int status);
void	take_a_fork();
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

#endif