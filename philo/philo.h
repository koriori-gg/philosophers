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
	TAKE_A_FORK,
	EAT,
	SLEEP,
	THINK,
	DIED
};

typedef struct s_philo {
	long			id;
	long			eat_count;
	long			last_eat_time;
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

//init
void	init_simulation(int argc, char **argv, t_simulation *simulation);
//simulation
void	start_simulation(t_simulation *simulation);
void	stop_simulation(t_simulation *simulation);
void	monitor(t_simulation *simulation);
//action
void	*philo_actions(void *arg);
void	print_message(t_philo *philo, long time);
//bool_handlers
bool	is_valid_argument(int argc, char **argv);
bool	is_dead(t_philo *philo);
//time
long	get_time(void);
void	wait_start_time(long start);
void	wait_time(long now, long time);
//libft
size_t	ft_strlen(const char *str);
long	ft_atol(const char *nptr);
int		ft_isdigit(int d);
#endif