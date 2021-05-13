#include "philo_one.h"

void	*monitor(void *arg)
{
	t_info	*info;
	int		i;

	info = (t_info *)arg;
	i = 0;
	while (*(info->is_dead) != info->num_of_people)
	{
		i++;
		if (i == info->num_of_people)
			i = 0;
	}
	return (NULL);
}
