#include "philo_one.h"

static int	main_loop(t_info *info, int ret)
{
	int	i;

	i = 0;
	while (ret != info->num_of_people)
	{
		if (pthread_mutex_lock(&(info->philos[i].let_mutex)))
			return (error_log(ERROR_MUTEX_LOCK));
		if (get_time() - info->philos[i].last_eat_time >= info->time_to_die)
		{
			philo_log(i + 1, LOG_DIED);
			*(info->is_dead) = info->num_of_people;
		}
		if (pthread_mutex_unlock(&(info->philos[i].let_mutex)))
			return (error_log(ERROR_MUTEX_UNLOCK));
		i++;
		if (i == info->num_of_people)
			i = 0;
		if (pthread_mutex_lock(info->is_dead_mutex))
			return (error_log(ERROR_MUTEX_LOCK));
		ret = *(info->is_dead);
		if (pthread_mutex_unlock(info->is_dead_mutex))
			return (error_log(ERROR_MUTEX_UNLOCK));
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
