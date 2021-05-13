#include "philo_one.h"

static int	philo_take_fork(t_philo *philo)
{
	int	ret;

	ret = pthread_mutex_lock(philo->left);
	if (ret)
		return (error_log(ERROR_MUTEX_LOCK));
	philo_log(philo->philo_nb, LOG_TAKEEN);
	ret = pthread_mutex_lock(philo->right);
	if (ret)
		return (error_log(ERROR_MUTEX_LOCK));
	philo_log(philo->philo_nb, LOG_TAKEEN);
	return (0);
}

static int	is_dead(t_philo *philo)
{
	long	now;
	int		ret;

	now = get_time();
	ret = 0;
	if (pthread_mutex_lock(philo->is_dead_mutex))
		return (error_log(ERROR_MUTEX_LOCK));
	if (*(philo->is_dead) == philo->num_of_people)
		ret = 1;
	/*
	else if ((now - philo->last_eat_time) >= philo->time_to_die)
	{
		ret = 1;
		*(philo->is_dead) = philo->num_of_people;
		philo_log(philo->philo_nb, LOG_DIED);
	}
	*/
	if (pthread_mutex_unlock(philo->is_dead_mutex))
		return (error_log(ERROR_MUTEX_UNLOCK));
	return (ret);
}

static int	philo_after_eat(t_philo *philo)
{
	philo_log(philo->philo_nb, LOG_EATING);
	if (pthread_mutex_lock(&(philo->let_mutex)))
		return (error_log(ERROR_MUTEX_LOCK));
	philo->last_eat_time = get_time();
	if (pthread_mutex_unlock(&(philo->let_mutex)))
		return (error_log(ERROR_MUTEX_UNLOCK));
	philo->eat_nb = philo->eat_nb + 1;
	if (pthread_mutex_lock(philo->is_dead_mutex))
		return (error_log(ERROR_MUTEX_LOCK));
	if (philo->eat_nb == philo->must_eat)
		*(philo->is_dead) = *(philo->is_dead) + 1;
	if (pthread_mutex_unlock(philo->is_dead_mutex))
		return (error_log(ERROR_MUTEX_UNLOCK));
	wait_time(philo->time_to_eat);
	if (pthread_mutex_unlock(philo->left))
		return (error_log(ERROR_MUTEX_UNLOCK));
	if (pthread_mutex_unlock(philo->right))
		return (error_log(ERROR_MUTEX_UNLOCK));
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
	if (pthread_mutex_lock(&(philo->let_mutex)))
		return (NULL);
	philo->last_eat_time = get_time();
	if (pthread_mutex_unlock(&(philo->let_mutex)))
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
