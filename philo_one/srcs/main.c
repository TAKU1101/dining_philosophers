#include "philo_one.h"

void	init_param(t_philo *philo, t_info *info)
{
	philo->num_of_people = info->num_of_people;
	philo->time_to_die = info->time_to_die;
	philo->time_to_eat = info->time_to_eat;
	philo->time_to_sleep = info->time_to_sleep;
	philo->must_eat = info->must_eat;
}

int	init_philos(int num, t_info *info)
{
	int		i;
	int		ret;
	t_philo	*philos;

	philos = (t_philo *)malloc(sizeof(t_philo) * num);
	if (philos == NULL)
		return (1);
	i = 0;
	while (i < num)
	{
		philos[i].last_eat_time = -1;
		ret = pthread_mutex_init(&(philos[i].let_mutex), NULL);
		philos[i].philo_nb = i;
		philos[i].eat_nb = 0;
		if (ret)
			return (1);
		init_param(&philos[i], info);
		i++;
	}
	// printf("philo nb: %d\n", philos[0].philo_nb);
	info->philos = philos;
	return (0);
}

int	init_info(t_info *info, int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (1);
	info->num_of_people = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->must_eat = -1;
	if (argc == 6)
	{
		info->must_eat = ft_atoi(argv[5]);
		if (info->must_eat < 0)
			return (1);
	}
	if (init_philos(info->num_of_people, info))
		return (1);
	return (0);
}

int main(int argc, char *argv[])
{
	t_info	info;

	if (init_info(&info, argc, argv))
		return (1);
	if (philo_exec(&info))
		return (1);
	if (philo_join(&info))
		return (1);
	return (0);
}
