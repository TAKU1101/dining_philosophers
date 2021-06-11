#include "philo_three.h"

static int	philo_wait(t_info *info)
{
	int	i;
	int	flag;
	int	status;

	i = 0;
	flag = 1;
	while (i < info->num_of_people)
	{
		waitpid(-1, &status, 0);
		if (flag && WSTOPSIG(status))
		{
			philo_log(WSTOPSIG(status) - 1, LOG_DIED);
			flag = 0;
		}
		if (status != SIGILL)
			kill_all_process(info);
		i++;
	}
	return (0);
}

int	philo_exec(t_info *info)
{
	int		i;

	i = 0;
	while (i < info->num_of_people)
	{
		info->philos[i].pid = fork();
		if (info->philos[i].pid == -1)
			return (error_log(ERROR_FORK));
		else if (!info->philos[i].pid)
		{
			pthread_create(&(info->philos[i].monitor), NULL, \
					monitor, (void *)&(info->philos[i]));
			philo_work((void *)(&info->philos[i]));
			exit(0);
		}
		i++;
	}
	pthread_create(&(info->counter_monitor), NULL, \
			count_monitor, (void *)info);
	philo_wait(info);
	return (0);
}
