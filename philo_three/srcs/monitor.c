#include "philo_three.h"

static int	main_loop(t_philo *philo, int ret)
{
	int	i;

	i = 0;
	while (ret != philo->num_of_people)
	{
		if (sem_wait(philo->let_bsem))
			return (error_log(ERROR_SEM_WAIT));
		if (get_time() - philo->last_eat_time >= philo->time_to_die)
		{
			// printf("%ld, %ld\n", get_time(), info->philos[i].last_eat_time);
			philo_log(i, LOG_DIED);
			exit(1);
			// *(philo->is_dead) = philo->num_of_people;
			// printf("%d %p in monitor\n", *(info->is_dead), info->is_dead);
		}
		if (sem_post(philo->let_bsem))
			return (error_log(ERROR_SEM_POST));
		/*
		i++;
		if (i == philo->num_of_people)
			i = 0;
		*/
		/*
		if (sem_wait(philo->is_dead_bsem))
			return (error_log(ERROR_SEM_WAIT));
		ret = *(philo->is_dead);
		if (sem_post(philo->is_dead_bsem))
			return (error_log(ERROR_SEM_POST));
		*/
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
	/*
	if (sem_wait(philo->is_dead_bsem))
		return (NULL);
	ret = *(philo->is_dead);
	if (sem_post(philo->is_dead_bsem))
		return (NULL);
	*/
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
	// all kill
	kill_all_process(info);
	return (NULL);
}
