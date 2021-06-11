#include "philo_one.h"

static int	main_loop(t_info *info, int ret)
{
	int	i;

	i = 0;
	while (ret != info->num_of_people)
	{
		if (pthread_mutex_lock(&(info->philos[i].let_mutex)))
			return (error_log(ERROR_MUTEX_LOCK));
		if (pthread_mutex_lock(info->is_dead_mutex))
			return (error_log(ERROR_MUTEX_LOCK));
		if (get_time() - info->philos[i].last_eat_time >= info->time_to_die)
		{
			philo_log(i, LOG_DIED, info->print_mutex);
			*(info->is_dead) = info->num_of_people;
		}
		ret = *(info->is_dead);
		if (pthread_mutex_unlock(info->is_dead_mutex))
			return (error_log(ERROR_MUTEX_UNLOCK));
		if (pthread_mutex_unlock(&(info->philos[i].let_mutex)))
			return (error_log(ERROR_MUTEX_UNLOCK));
		i++;
		if (i == info->num_of_people)
			i = 0;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_info	*info;
	int		i;
	int		ret;

	info = (t_info *)arg;
	i = 0;
	if (pthread_mutex_lock(info->is_dead_mutex))
		return (NULL);
	ret = *(info->is_dead);
	if (pthread_mutex_unlock(info->is_dead_mutex))
		return (NULL);
	if (main_loop(info, ret))
		return (NULL);
	return (NULL);
}
