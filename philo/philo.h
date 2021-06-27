#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

struct	s_philo;
struct	s_ph;

typedef struct s_philo
{
	int				philo_num;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	int				meal_num;
	uint64_t		die_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_philo;
	pthread_mutex_t	message;
	struct s_ph		*ph;
	u_int64_t		start;
}					t_philo;

typedef struct s_ph
{
	pthread_t		thread;
	pthread_mutex_t	check;
	int				dead;
	int				have_eaten;
	int				left_fork;
	int				right_fork;
	int				number;
	t_philo			*all;
	uint64_t		last_meal;
	uint64_t		time_to_death;
}				t_ph;

int			ft_atoi(const char *str);
int			pre_philo(t_philo *philo);
uint64_t	get_time(void);
void		*checker(void *ph);
void		*check_m(void *ph);
void		clean(t_philo *philo);
int			make_forks(t_philo *philo);
int			init_philos(t_philo *philo);
int			start_philosophizing(t_philo *philo);
void		message(char *str, t_ph *phil);

#endif