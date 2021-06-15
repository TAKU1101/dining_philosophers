#include "philo_one.h"

static void	init_param(t_philo *philo, t_info *info)
{
	philo->num_of_people = info->num_of_people;
	philo->time_to_die = info->time_to_die;
	philo->time_to_eat = info->time_to_eat;
	philo->time_to_sleep = info->time_to_sleep;
	philo->must_eat = info->must_eat;
}

static int	init_philo(t_info *info, int *is_dead, \
						pthread_mutex_t *is_dead_mutex, \
						pthread_mutex_t *print_mutex)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = info->philos;
	while (i < info->num_of_people)
	{
		if (pthread_mutex_init(&(philos[i].let_mutex), NULL))
			return (error_log(ERROR_MUTEX_INIT));
		philos[i].last_eat_time = -1;
		philos[i].philo_nb = i;
		philos[i].eat_nb = 0;
		init_param(&(philos[i]), info);
		philos[i].left = &(info->forks[i]);
		philos[i].right = &(info->forks[(i + 1) % info->num_of_people]);
		philos[i].is_dead = is_dead;
		philos[i].is_dead_mutex = is_dead_mutex;
		philos[i].print_mutex = print_mutex;
		i++;
	}
	return (0);
}

static int	init_philos(int num, t_info *info)
{
	int				*is_dead;
	t_philo			*philos;
	pthread_mutex_t	*is_dead_mutex;
	pthread_mutex_t	*print_mutex;

	if (!wrap_malloc(&philos, sizeof(t_philo) * num))
		return (error_log(ERROR_MALLOC));
	info->philos = philos;
	if (!wrap_malloc(&is_dead, sizeof(int)))
		return (error_log(ERROR_MALLOC));
	*is_dead = 0;
	info->is_dead = is_dead;
	if (!wrap_malloc(&is_dead_mutex, sizeof(pthread_mutex_t)))
		return (error_log(ERROR_MALLOC));
	if (pthread_mutex_init(is_dead_mutex, NULL))
		return (error_log(ERROR_MUTEX_INIT));
	if (!wrap_malloc(&print_mutex, sizeof(pthread_mutex_t)))
		return (error_log(ERROR_MUTEX_INIT));
	if (pthread_mutex_init(print_mutex, NULL))
		return (error_log(ERROR_MUTEX_INIT));
	info->is_dead_mutex = is_dead_mutex;
	info->print_mutex = print_mutex;
	init_philo(info, is_dead, is_dead_mutex, print_mutex);
	return (0);
}

static int	init_fork(t_info *info, int n)
{
	int				i;
	int				ret;
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
		if (info->must_eat <= 0)
			return (error_log(ERROR_PARAM));
	}
	if (check_param(info))
		return (1);
	if (init_fork(info, info->num_of_people))
		return (1);
	if (init_philos(info->num_of_people, info))
		return (1);
	return (0);
}
