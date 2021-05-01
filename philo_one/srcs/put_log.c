#include "philo_one.h"

int error_log(char *err_msg)
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
