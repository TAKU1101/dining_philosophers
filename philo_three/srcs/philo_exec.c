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
			philo_work((void *)(&info->philos[i]));
			break;
		}
		i++;
	}
	if (pid)
	{
		pid = fork();
		if (pid == -1)
			return (error_log(ERROR_FORK));
		else if (!pid)
		{
			monitor((void *)info);
		}
		printf("after %d\n", i);
	}
	i = 0;
	while (i < info->num_of_people + 1)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	return (0);
}
