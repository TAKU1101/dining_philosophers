#include "philo_two.h"

static int	is_dead(t_philo *philo)
{
	long	now;
	int		ret;

	now = get_time();
	ret = 0;
	if (sem_wait(philo->is_dead_bsem))
		return (error_log(ERROR_SEM_WAIT));
	if (*(philo->is_dead) == philo->num_of_people)
		ret = 1;
	if (sem_post(philo->is_dead_bsem))
		return (error_log(ERROR_SEM_POST));
	return (ret);
}

static int	philo_take_fork(t_philo *philo)
{
	if (sem_wait(philo->fork_sem))
		return (error_log(ERROR_SEM_WAIT));
	if (!is_dead(philo))
		philo_log(philo->philo_nb, LOG_TAKEEN);
	if (sem_wait(philo->fork_sem))
		return (error_log(ERROR_SEM_WAIT));
	if (!is_dead(philo))
		philo_log(philo->philo_nb, LOG_TAKEEN);
	return (0);
}

static int	philo_put_fork(t_philo *philo)
{
	if (sem_post(philo->fork_sem))
		return (error_log(ERROR_SEM_POST));
	if (sem_post(philo->fork_sem))
		return (error_log(ERROR_SEM_POST));
	return (0);
}

static int	philo_after_eat(t_philo *philo)
{
	if (!is_dead(philo))
		philo_log(philo->philo_nb, LOG_EATING);
	if (sem_wait(philo->let_bsem))
		return (error_log(ERROR_SEM_WAIT));
	philo->last_eat_time = get_time();
	if (sem_post(philo->let_bsem))
		return (error_log(ERROR_SEM_POST));
	philo->eat_nb = philo->eat_nb + 1;
	if (sem_wait(philo->is_dead_bsem))
		return (error_log(ERROR_SEM_WAIT));
	if (philo->eat_nb == philo->must_eat)
		*(philo->is_dead) = *(philo->is_dead) + 1;
	if (sem_post(philo->is_dead_bsem))
		return (error_log(ERROR_SEM_POST));
	wait_time(philo->time_to_eat);
	if (philo_put_fork(philo))
		return (1);
	if (is_dead(philo))
		return (1);
	philo_log(philo->philo_nb, LOG_SLEEPING);
	wait_time(philo->time_to_sleep);
	if (is_dead(philo))
		return (1);
	philo_log(philo->philo_nb, LOG_THINKING);
	return (0);
}

void	*philo_work(void *arg)
{
	t_philo	*philo;
	int		ret;

	philo = (t_philo *)arg;
	if (sem_wait(philo->let_bsem))
		return (NULL);
	philo->last_eat_time = get_time();
	if (sem_post(philo->let_bsem))
		return (NULL);
	if (philo->philo_nb % 2)
		usleep(200);
	ret = 0;
	while (!ret)
	{
		philo_take_fork(philo);
		ret = philo_after_eat(philo);
	}
	return (NULL);
}
