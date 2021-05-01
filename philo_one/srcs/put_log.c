#include "philo_one.h"

int	error_log(char *err_msg)
{
	int i;

	i = 0;
	while (err_msg[i])
	{
		write(2, &err_msg[i], 1);
		i++;
	}
	write(2, "\n", 1);
	return (1);
}

long	get_time()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	philo_log(int nb, char *log)
{
	printf("%ld %d %s\n", get_time(), nb, log);
	return (0);
}
