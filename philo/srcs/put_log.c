#include "philo_one.h"

int	error_log(char *err_msg)
{
	int	i;

	i = 0;
	while (err_msg[i])
	{
		write(2, &err_msg[i], 1);
		i++;
	}
	write(2, "\n", 1);
	return (1);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	philo_log(int nb, char *log, pthread_mutex_t *print_mutex)
{
	if (pthread_mutex_lock(print_mutex))
		return (error_log(ERROR_MUTEX_LOCK));
	printf("%ld %d %s\n", get_time(), nb, log);
	if (pthread_mutex_unlock(print_mutex))
		return (error_log(ERROR_MUTEX_UNLOCK));
	return (0);
}

void	one_log(t_info *info)
{
	printf("%ld %d %s\n", get_time(), 0, LOG_TAKEEN);
	wait_time(info->time_to_die);
	printf("%ld %d %s\n", get_time(), 0, LOG_DIED);
}
