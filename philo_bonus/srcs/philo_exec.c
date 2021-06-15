#include "philo_three.h"

static void	put_last_log(int status)
{
	ft_putnbr_fd(get_time(), 1);
	write(1, " ", 1);
	ft_putnbr_fd(WSTOPSIG(status), 1);
	write(1, " ", 1);
	ft_putstr_fd(LOG_DIED, 1);
	write(1, "\n", 1);
}

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
			if (sem_wait(info->print_bsem))
				return (error_log(ERROR_SEM_WAIT));
			put_last_log(status);
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
