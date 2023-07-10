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
};

typedef struct s_philo {
	long				id;
	long				eat_count;
	long				last_eat_time;
	long				next_eat_time;
	int					state;
	long				now;
	bool				one_philo;
	pthread_t			thread;
	pthread_mutex_t		philo_mutex;
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
	pthread_t		monitor_thread;
	pthread_mutex_t	stop_mutex;
	t_philo			*philo;
}	t_simulation;

//init
int		init_simulation(int argc, char **argv, t_simulation *simulation);
//simulation
int		start_simulation(t_simulation *simulation);
int		stop_simulation(t_simulation *simulation, int count);
void	*monitor(void *arg);
void	*philo_life_cycle(void *arg);
//fork
void	put_down_fork(pthread_mutex_t *fork_a, pthread_mutex_t *fork_b);
int		philo_take_fork(t_philo *philo);
int		pick_up_fork(t_philo *philo,
			pthread_mutex_t *fork_a, pthread_mutex_t *fork_b);
//action
int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		philo_think(t_philo *philo);
//print_message
int		update_philo(t_philo *philo, char *message, int state);
void	print_dead(t_philo *philo,long id, long now, char *message);
//bool_handlers
bool	is_valid_argument(int argc, char **argv);
bool	should_stop(t_philo *philo);
bool	has_finished_eat(t_simulation *simulation);
bool	is_same_state(t_philo *philo, int state);
bool	is_dead(t_philo *philo, long now);
//change_data
void	change_state(t_philo *philo, int state);
void	add_eat_count(t_philo *philo);
void	update_last_eat_time(t_philo *philo, long now);
void	update_stop(t_philo *philo);
void	set_next_eat_time(t_philo *philo);
//cal
long	calculate_next_eat_in_odd(t_philo *philo);
//time
long	get_time(void);
void	wait_start_time(long start);
void	wait_time(long start, long time);
//libft
size_t	ft_strlen(const char *str);
long	ft_atol(const char *nptr);
int		ft_isdigit(int d);
bool	is_number(char *str);
//pthread
int		ft_pthread_create(pthread_t *thread, void *func, t_philo *philo_i, int i);
//free
int		join_all_thread(t_simulation *simulation, int count);
int		free_all_mutex(t_simulation *simulation, int count);
#endif