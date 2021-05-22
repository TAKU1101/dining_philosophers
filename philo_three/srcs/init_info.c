#include "philo_three.h"

static void	init_param(t_philo *philo, t_info *info)
{
	philo->num_of_people = info->num_of_people;
	philo->time_to_die = info->time_to_die;
	philo->time_to_eat = info->time_to_eat;
	philo->time_to_sleep = info->time_to_sleep;
	philo->must_eat = info->must_eat;
}

static int	init_philo(t_info *info)
//static int	init_philo(t_info *info, int *is_dead, 
//						sem_t *is_dead_bsem)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = info->philos;
	while (i < info->num_of_people)
	{
		philos[i].let_bsem = sem_open_number(i, "/philo_three_let_", 1);
		philos[i].last_eat_time = get_time();
		philos[i].philo_nb = i;
		// philos[i].eat_nb = 0;
		philos[i].eat_count = sem_open_number(i, "/philo_three_eat_count_", 0);
		init_param(&philos[i], info);
		philos[i].fork_sem = info->fork_sem;
		// philos[i].is_dead = is_dead;
		// philos[i].is_dead_bsem = is_dead_bsem;
		i++;
	}
	return (0);
}

static int	init_philos(int num, t_info *info)
{
	/*
	int		*is_dead;
	sem_t	*is_dead_bsem;
	*/
	t_philo	*philos;

	philos = (t_philo *)malloc(sizeof(t_philo) * num);
	if (philos == NULL)
		return (error_log(ERROR_MALLOC));
	info->philos = philos;
	/*
	is_dead = (int *)malloc(sizeof(int));
	if (is_dead == NULL)
		return (error_log(ERROR_MALLOC));
	*is_dead = 0;
	info->is_dead = is_dead;
	sem_unlink("/philo_three_is_dead_bsem");
	is_dead_bsem = sem_open("/philo_three_is_dead_bsem", O_CREAT, 0600, 1);
	if (is_dead_bsem == NULL)
		return (error_log(ERROR_SEM_OPEN));
	info->is_dead_bsem = is_dead_bsem;
	init_philo(info, is_dead, is_dead_bsem);
	*/
	init_philo(info);
	return (0);
}

static int	init_fork(t_info *info, int n)
{
	sem_t	*fork;

	sem_unlink("/philo_three_fork");
	fork = sem_open("/philo_three_fork", O_CREAT, 0600, n);
	if (fork == NULL)
		return (error_log(ERROR_SEM_OPEN));
	info->fork_sem = fork;
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
	if (check_param(info))
		return (1);
	if (init_fork(info, info->num_of_people))
		return (1);
	if (init_philos(info->num_of_people, info))
		return (1);
	return (0);
}
