#include "philo_three.h"

int	kill_all_process(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_people)
	{
		kill(info->philos[i].pid, SIGILL);
		i++;
	}
	return (0);
}
