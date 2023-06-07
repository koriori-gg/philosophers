#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>

enum e_state {
	EAT,
	SLEEP,
	THINK,
	DIED
};

typedef struct s_philo {
	long			id;
	long			eat_count;
	int				state;
	pthread_t		thread;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	struct s_simulation	*simulation;
}	t_philo;

typedef struct s_simulation {
	long	num_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	must_eat;
	long	start;
	t_philo	*philo;
}	t_simulation;

void	init_simulation(int argc, char **argv, t_simulation *simulation);
void	*philo_actions(void *arg);
bool	is_dead(t_philo *philo);
long	get_time(void);
long	ft_atol(const char *nptr);
int		ft_isdigit(int d);
#endif