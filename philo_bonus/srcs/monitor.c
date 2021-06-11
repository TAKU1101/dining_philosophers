#include "philo_three.h"

static int	main_loop(t_philo *philo, int ret)
{
	int	i;

	i = 0;
	while (ret != philo->num_of_people)
	{
		if (sem_wait(philo->let_bsem))
			return (error_log(ERROR_SEM_WAIT));
		if (get_time() - philo->last_eat_time > philo->time_to_die)
		{
			exit(1 + philo->philo_nb);
		}
		if (sem_post(philo->let_bsem))
			return (error_log(ERROR_SEM_POST));
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	int		i;
	int		ret;

	philo = (t_philo *)arg;
	i = 0;
	ret = 0;
	if (main_loop(philo, ret))
		return (NULL);
	return (NULL);
}

void	*count_monitor(void *arg)
{
	t_info	*info;
	int		i;
	int		j;

	info = (t_info *)arg;
	if (info->must_eat == -1)
		return (NULL);
	i = 0;
	while (i < info->num_of_people)
	{
		j = 0;
		while (j < info->must_eat)
		{
			sem_wait(info->philos[i].eat_count);
			j++;
		}
		i++;
	}
	kill_all_process(info);
	return (NULL);
}
