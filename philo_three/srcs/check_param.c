#include "philo_three.h"

int	check_param(t_info *info)
{
	if (info->num_of_people <= 0 || 200 < info->num_of_people)
		return (error_log(ERROR_PARAM));
	if (info->time_to_die < 50)
		return (error_log(ERROR_PARAM));
	if (info->time_to_eat < 50)
		return (error_log(ERROR_PARAM));
	if (info->time_to_sleep < 50)
		return (error_log(ERROR_PARAM));
	return (0);
}
