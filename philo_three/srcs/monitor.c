#include "philo_three.h"

static int	main_loop(t_info *info, int ret)
{
	int	i;

	i = 0;
	while (ret != info->num_of_people)
	{
		if (sem_wait(info->philos[i].let_bsem))
			return (error_log(ERROR_SEM_WAIT));
		if (get_time() - info->philos[i].last_eat_time >= info->time_to_die)
		{
			// printf("%ld, %ld\n", get_time(), info->philos[i].last_eat_time);
			philo_log(i, LOG_DIED);
			*(info->is_dead) = info->num_of_people;
			// printf("%d %p in monitor\n", *(info->is_dead), info->is_dead);
		}
		if (sem_post(info->philos[i].let_bsem))
			return (error_log(ERROR_SEM_POST));
		i++;
		if (i == info->num_of_people)
			i = 0;
		if (sem_wait(info->is_dead_bsem))
			return (error_log(ERROR_SEM_WAIT));
		ret = *(info->is_dead);
		if (sem_post(info->is_dead_bsem))
			return (error_log(ERROR_SEM_POST));
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
	if (sem_wait(info->is_dead_bsem))
		return (NULL);
	ret = *(info->is_dead);
	if (sem_post(info->is_dead_bsem))
		return (NULL);
	if (main_loop(info, ret))
		return (NULL);
	return (NULL);
}
