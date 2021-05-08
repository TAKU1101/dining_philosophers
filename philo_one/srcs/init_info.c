#include "philo_one.h"

static void	init_param(t_philo *philo, t_info *info)
{
	philo->num_of_people = info->num_of_people;
	philo->time_to_die = info->time_to_die;
	philo->time_to_eat = info->time_to_eat;
	philo->time_to_sleep = info->time_to_sleep;
	philo->must_eat = info->must_eat;
}

static int	init_philo(t_philo *philo, t_info *info, int i)
{
	int ret;

	philo->last_eat_time = -1;
	ret = pthread_mutex_init(&(philo->let_mutex), NULL);
	philo->philo_nb = i;
	philo->eat_nb = 0;
	if (ret)
		return (error_log(ERROR_MUTEX_INIT));
	init_param(philo, info);
	philo->left = &(info->forks[i]);
	philo->right = &(info->forks[(i + 1) % info->num_of_people]);
	return (0);
}

static int	init_philos(int num, t_info *info)
{
	int		i;
//	int		ret;
	t_philo	*philos;

	philos = (t_philo *)malloc(sizeof(t_philo) * num);
	if (philos == NULL)
		return (error_log(ERROR_MALLOC));
	i = 0;
	while (i < num)
	{
		if (init_philo(&(philos[i]), info, i))
			return (1);
		i++;
	}
	info->philos = philos;
	return (0);
}

static int	init_fork(t_info *info, int n)
{
	int i;
	int	ret;
	pthread_mutex_t	*forks;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n);
	if (forks == NULL)
		return (error_log(ERROR_MALLOC));
	i = 0;
	while (i < n)
	{
		ret = pthread_mutex_init(&(forks[i]), NULL);
		if (ret)
			return (error_log(ERROR_MALLOC));
		i++;
	}
	info->forks = forks;
	return (0);
}

int	init_info(t_info *info, int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (error_log(ERROR_PARAM_NUM));
	info->num_of_people = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->must_eat = -1;
	if (argc == 6)
	{
		info->must_eat = ft_atoi(argv[5]);
		if (info->must_eat < 0)
			return (error_log(ERROR_PARAM));
	}
	if (init_fork(info, info->num_of_people))
		return (1);
	if (init_philos(info->num_of_people, info))
		return (1);
	return (0);
}
