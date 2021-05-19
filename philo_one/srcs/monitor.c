#include "philo_one.h"

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
	while (ret != info->num_of_people)
	{
		if (pthread_mutex_lock(&(info->philos[i].let_mutex)))
			return (NULL);
		if (get_time() - info->philos[i].last_eat_time >= info->time_to_die)
		{
			philo_log(i + 1, LOG_DIED);
			*(info->is_dead) = info->num_of_people;
		}
		if (pthread_mutex_unlock(&(info->philos[i].let_mutex)))
			return (NULL);
		i++;
		if (i == info->num_of_people)
			i = 0;
		if (pthread_mutex_lock(info->is_dead_mutex))
			return (NULL);
		ret = *(info->is_dead);
		if (pthread_mutex_unlock(info->is_dead_mutex))
			return (NULL);
	}
	return (NULL);
}
