#include "philo_two.h"

/*
static int	init_fork(t_info *info, int n)
{
	sem_t	*fork;

	fork = sem_open("/test", O_CREAT, 0600, n);
	if (fork == NULL)
		return (error_log(""));
	return (0);
}
*/

int	init_info(t_info *info, int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (error_log(ERROR_PARAM_NUM));
	info->num_of_people = ft_atoi(argv[0]);
	info->time_to_die = ft_atoi(argv[1]);
	info->time_to_eat = ft_atoi(argv[2]);
	info->time_to_sleep = ft_atoi(argv[3]);
	info->must_eat = -1;
	if (argc == 6)
	{
		info->must_eat = ft_atoi(argv[4]);
		if (info->must_eat < 0)
			return (error_log(ERROR_PARAM));
	}
	if (check_param(info))
		return (1);
	return (0);
}
