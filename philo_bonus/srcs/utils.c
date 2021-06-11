#include "philo_three.h"

void	wait_time(long time)
{
	long	start_time;

	start_time = get_time();
	while (get_time() < start_time + time)
	{
		usleep(500);
	}
}

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

int	philo_log(int nb, char *log, sem_t *print_bsem)
{
	if (sem_wait(print_bsem))
		return (error_log(ERROR_SEM_WAIT));
	// printf("%ld %d %s\n", get_time(), nb, log);
	ft_putnbr_fd(get_time(), 1);
	write(1, " ", 1);
	ft_putnbr_fd(nb, 1);
	write(1, " ", 1);
	ft_putstr_fd(log, 1);
	write(1, "\n", 1);
	if (sem_post(print_bsem))
		return (error_log(ERROR_SEM_POST));
	return (0);
}
