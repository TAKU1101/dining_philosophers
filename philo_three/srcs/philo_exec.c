#include "philo_three.h"

int	philo_exec(t_info *info)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < info->num_of_people)
	{
		pid = fork();
		if (pid == -1)
			return (error_log(ERROR_FORK));
		else if (!pid)
		{
			// info->philos[i].last_eat_time = get_time();
			// printf("%d: %p\n", i, &(info->philos[i].last_eat_time));
			pthread_create(&(info->philos[i].monitor), NULL, \
					monitor, (void *)&(info->philos[i]));
			philo_work((void *)(&info->philos[i]));
			exit(0);
		}
		i++;
	}
	/*
	if (pid)
	{
		pid = fork();
		if (pid == -1)
			return (error_log(ERROR_FORK));
		else if (!pid)
		{
			// printf("monidor: %p\n", &(info->philos[0].last_eat_time));
			monitor((void *)info);
			exit(0);
		}
		printf("after %d\n", i);
	}
	*/
	i = 0;
	while (i < info->num_of_people + 1)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	return (0);
}
