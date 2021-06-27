#include "philo.h"

void	live_loop(void *ph)
{
	t_ph	*phil;

	phil = (t_ph *)ph;
	// if (phil->number == phil->all->philo_num - 1)
	// {
	// 	pthread_mutex_lock(&phil->all->forks[phil->left_fork]);
	// message("has taken a fork", ph);
	// pthread_mutex_lock(&phil->all->forks[phil->right_fork]);
	// message("has taken a fork", ph);
	// message("is eating", ph);
	// usleep(phil->all->eat_time * 1000);
	// pthread_mutex_unlock(&phil->all->forks[phil->left_fork]);
	// pthread_mutex_unlock(&phil->all->forks[phil->right_fork]);
	// phil->have_eaten += 1;
	// phil->time_to_death = get_time() + phil->all->die_time;
	// message("is sleeping", ph);
	// usleep(phil->all->sleep_time * 1000);
	// message("is thinking", ph);
	// }
	// else{
	pthread_mutex_lock(&phil->all->forks[phil->left_fork]);
	message("has taken a fork", ph);
	pthread_mutex_lock(&phil->all->forks[phil->right_fork]);
	message("has taken a fork", ph);
	message("is eating", ph);
	usleep(phil->all->eat_time * 1000);
	pthread_mutex_unlock(&phil->all->forks[phil->right_fork]);
	pthread_mutex_unlock(&phil->all->forks[phil->left_fork]);
	phil->have_eaten += 1;
	phil->time_to_death = get_time() + phil->all->die_time;
	message("is sleeping", ph);
	usleep(phil->all->sleep_time * 1000);
	message("is thinking", ph);
}

void	*live(void *ph)
{
	t_ph		*p;
	pthread_t	tid;

	p = (t_ph *)ph;
	p->last_meal = get_time();
	p->time_to_death = p->last_meal + p->all->die_time;
	if (pthread_create(&tid, NULL, &checker, ph) != 0)
		return ((void *)1);
	pthread_detach(tid);
	// if (p->number % 2 == 0)
	// 	usleep(100);
	while (1)
	{
		live_loop(p);
	}
	return (NULL);
}

int	start_philosophizing(t_philo *philo)
{
	int			i;
	pthread_t	tid1;

	i = 0;
	philo->start = get_time();
	if (philo->meal_num != -1)
	{
		if (pthread_create(&tid1, NULL, &check_m, philo) != 0)
			return (1);
		// pthread_detach(tid1);
	}
	while (i < philo->philo_num)
	{
		philo->ph[i].time_to_death = get_time() + philo->ph[i].all->die_time;
		if (pthread_create(&philo->ph[i].thread, \
			NULL, &live, (void *)(&philo->ph[i])) != 0)
			return (-1);
		pthread_detach(philo->ph[i].thread);
		// usleep(100);
		i++;
	}
	return (0);
}

int	init_philos(t_philo *philo)
{
	int	i;

	i = 0;
	philo->ph = (t_ph *)malloc(sizeof(t_ph) * philo->philo_num);
	if (philo->ph == NULL)
		return (-1);
	while (i < philo->philo_num)
	{
		philo->ph[i].last_meal = 0;
		philo->ph[i].dead = 0;
		philo->ph[i].have_eaten = 0;
		philo->ph[i].number = i + 1;
		philo->ph[i].left_fork = i;
		if (i == philo->philo_num - 1)
			philo->ph[i].right_fork = 0;
		else
			philo->ph[i].right_fork = i + 1;
		philo->ph[i].all = philo;
		i++;
	}
	return (0);
}

int	make_forks(t_philo *philo)
{
	int	i;

	i = 0;
	philo->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
		philo->philo_num);
	if (philo->forks == NULL)
		return (-1);
	i = 0;
	while (i < philo->philo_num)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&philo->message, NULL);
	pthread_mutex_init(&philo->dead_philo, NULL);
	pthread_mutex_lock(&philo->dead_philo);
	return (0);
}
