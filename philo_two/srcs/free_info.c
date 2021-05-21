#include "philo_two.h"

static int	sem_free(t_info *info)
{
	int		i;

	i = 0;
	if (sem_close(info->fork_sem))
		return (error_log(ERROR_SEM_CLOSE));
	sem_unlink("/philo_two_fork");
	if (sem_close(info->is_dead_bsem))
		return (error_log(ERROR_SEM_CLOSE));
	sem_unlink("/philo_two_is_dead_bsem");
	while (i < info->num_of_people)
	{
		if (sem_close_number(info->philos[i].let_bsem, i))
			return (1);
		i++;
	}
	free(info->philos);
	info->philos = NULL;
	return (0);
}

int	free_info(t_info *info)
{
	free(info->is_dead);
	info->is_dead = NULL;
	sem_free(info);
	return (0);
}
