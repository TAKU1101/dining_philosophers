#include "philo_one.h"

int	check_num_of_people(t_info *info)
{
	if (info->num_of_people == 1)
	{
		one_log(info);
		return (1);
	}
	return (0);
}

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
	if (check_num_of_people(info))
		return (1);
	return (0);
}
