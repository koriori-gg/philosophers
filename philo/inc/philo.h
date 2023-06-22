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
	WAIT,
	EAT,
	SLEEP,
	THINK,
	DIED
};

typedef struct s_philo {
	long				id;
	long				eat_count;
	long				last_eat_time;
	long				wait_time;
	int					state;
	pthread_t			thread;
	pthread_mutex_t		l_fork;
	pthread_mutex_t		*r_fork;
	struct s_simulation	*simulation;
}	t_philo;

typedef struct s_simulation {
	long			num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat;
	long			start;
	bool			stop;
	pthread_mutex_t	mutex;
	t_philo			*philo;
}	t_simulation;

//init
void	init_simulation(int argc, char **argv, t_simulation *simulation);
//simulation
void	start_simulation(t_simulation *simulation);
void	stop_simulation(t_simulation *simulation);
void	monitor(t_simulation *simulation);
void	*philo_life_cycle(void *arg);
//action
void	philo_take_fork(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
//print_message
bool	print_message(t_philo *philo, long time);
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
bool	is_number(char *str);
//pthread
void	ft_pthread_mutex_lock(pthread_mutex_t *mtx);
void	ft_pthread_mutex_unlock(pthread_mutex_t *mtx);
void	ft_pthread_mutex_destroy(pthread_mutex_t *mtx);
void	ft_pthread_create(pthread_t *thread, void *func, t_philo *philo_i);
void	ft_pthread_join(pthread_t thread);
#endif