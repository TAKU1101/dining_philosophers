#include "philo_one.h"

int	philo_exec(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_people)
	{
		pthread_create(&(info->philos[i].thread), NULL, \
					philo_work, (void *)&(info->philos[i]));
		i++;
	}
	printf("before exec: %p\n", info->is_dead);
	pthread_create(&(info->monitor), NULL, monitor, (void *)info);
	return (0);
}

int	philo_join(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_people)
	{
		pthread_join(info->philos[i].thread, NULL);
		i++;
	}
	return (0);
}
