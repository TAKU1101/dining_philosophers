#include "philo_three.h"

int	kill_all_process(t_info *info)
{
	int	i;
	int ret;

	i = 0;
	while (i < info->num_of_people)
	{
		ret = kill(info->philos[i].pid, SIGILL);
		i++;
	}
	return (0);
}
