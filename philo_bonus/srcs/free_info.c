#include "philo_three.h"

int	free_info(t_info *info)
{
	int	i;

	sem_close(info->fork_sem);
	sem_unlink("/philo_three_fork");
	sem_close(info->print_bsem);
	sem_unlink("/philo_three_print_bsem");
	i = 0;
	while (i < info->num_of_people)
	{
		sem_close_number(info->philos[i].let_bsem, i, "/philo_three_let_");
		sem_close_number(info->philos[i].eat_count, i, \
				"/philo_three_eat_count_");
		i++;
	}
	free(info->philos);
	info->philos = NULL;
	return (0);
}
