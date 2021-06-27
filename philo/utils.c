#include "philo.h"

int	ft_atoi(const char *str)
{
	int			sign;
	int			result;

	sign = 1;
	result = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v' || \
			*str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

uint64_t	get_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (uint64_t)1000) + time.tv_usec / 1000);
}

void	clean(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&philo->dead_philo);
	pthread_mutex_destroy(&philo->message);
	i = 0;
	while (i < philo->philo_num)
	{
		pthread_mutex_destroy(&philo->forks[i]);
		i++;
	}
	free(philo->forks);
	pthread_mutex_destroy(&philo->dead_philo);
}

void	message(char *str, t_ph *phil)
{
	pthread_mutex_lock(&phil->all->message);
	printf("%llu %d %s\n", get_time() - phil->all->start, phil->number, str);
	pthread_mutex_unlock(&phil->all->message);
}
