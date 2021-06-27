#include "philo.h"

void	init_data(t_philo *philo)
{
	philo->philo_num = -1;
	philo->eat_time = -1;
	philo->sleep_time = -1;
	philo->meal_num = -1;
	philo->die_time = -1;
}

int	check_args(t_philo *philo)
{
	if (philo->philo_num < 1 || philo->sleep_time < 1 || \
		philo->die_time < 1 || philo->eat_time < 1)
		return (-1);
	return (1);
}

int	get_args(t_philo *philo, char **argv, int argc)
{
	init_data(philo);
	philo->philo_num = ft_atoi(argv[1]);
	philo->die_time = ft_atoi(argv[2]);
	philo->eat_time = ft_atoi(argv[3]);
	philo->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
	{
		philo->meal_num = ft_atoi(argv[5]);
		if (philo->meal_num < 1)
			return (-1);
	}
	if (check_args(philo) == -1)
		return (-1);
	return (1);
}

int	pre_philo(t_philo *philo)
{
	if (init_philos(philo) == -1)
		return (-1);
	if (make_forks(philo) == -1)
		return (-1);
	start_philosophizing(philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc > 6 || argc < 5)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	else
	{
		if (get_args(&philo, argv, argc) == -1)
		{
			printf("Error: arguments\n");
			return (1);
		}
		pre_philo(&philo);
	}
	pthread_mutex_lock(&philo.dead_philo);
	return (0);
}
