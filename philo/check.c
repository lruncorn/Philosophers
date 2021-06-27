#include "philo.h"

void	*check_m(void *ph)
{
	t_philo		*phil;
	int			i;

	phil = (t_philo *)ph;
	while (1)
	{
		i = 0;
		while (i < phil->philo_num)
		{
			if (phil->ph[i].have_eaten < phil->meal_num)
				break ;
			i++;
		}
		if (i == phil->philo_num)
			break ;
		usleep(1000);
	}
	pthread_mutex_lock(&phil->message);
	printf("All philos are well-fed\n");
	pthread_mutex_unlock(&phil->dead_philo);
	return (NULL);
}

void	*checker(void *ph)
{
	t_ph		*phil;

	phil = (t_ph *)ph;
	while (1)
	{
		pthread_mutex_lock(&phil->check);
		if (get_time() > phil->time_to_death)
		{
			pthread_mutex_lock(&phil->all->message);
			printf("%llu %d died\n", get_time() - \
				phil->all->start, phil->number);
			pthread_mutex_unlock(&phil->check);
			pthread_mutex_unlock(&phil->all->dead_philo);
			return (NULL);
		}
		pthread_mutex_unlock(&phil->check);
		usleep(1000);
	}
}
