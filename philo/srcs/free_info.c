#include "philo_one.h"

static int	mutex_destroy(t_info *info)
{
	int				i;
	pthread_mutex_t	*forks;

	if (pthread_mutex_destroy(info->philos[0].is_dead_mutex))
		return (error_log(ERROR_MUTEX_DESTROY));
	free(info->philos[0].is_dead_mutex);
	info->philos[0].is_dead_mutex = NULL;
	if (pthread_mutex_destroy(info->print_mutex))
		return (error_log(ERROR_MUTEX_DESTROY));
	free(info->print_mutex);
	info->print_mutex = NULL;
	i = 0;
	forks = info->forks;
	while (i < info->num_of_people)
	{
		if (pthread_mutex_destroy(&(forks[i])))
			return (error_log(ERROR_MUTEX_DESTROY));
		i++;
	}
	free(info->forks);
	info->forks = NULL;
	free(info->philos);
	info->philos = NULL;
	return (0);
}

int	free_info(t_info *info)
{
	free(info->philos[0].is_dead);
	info->philos[0].is_dead = NULL;
	mutex_destroy(info);
	return (0);
}
