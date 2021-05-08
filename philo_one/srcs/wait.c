#include "philo_one.h"

void	wait_time(long time)
{
	long	start_time;

	start_time = get_time();
	while (get_time() < start_time + time)
	{
		usleep(500);
	}
}
