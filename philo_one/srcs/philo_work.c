#include "philo_one.h"

static int	philo_take_fork(t_philo *philo)
{
	int ret;

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

static int	philo_after_eat(t_philo *philo)
{
	philo_log(philo->philo_nb, LOG_EATING);
	usleep(philo->time_to_eat * 1000);
	if (pthread_mutex_unlock(philo->left))
		return (error_log(ERROR_MUTEX_UNLOCK));
	if (pthread_mutex_unlock(philo->right))
		return (error_log(ERROR_MUTEX_UNLOCK));
	philo_log(philo->philo_nb, LOG_SLEEPING);
	usleep(philo->time_to_sleep * 1000);
	philo_log(philo->philo_nb, LOG_THINKING);
	return (0);
}

void	*philo_work(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_nb % 2)
		usleep(200);
	while (1)
	{
		philo_take_fork(philo);
		philo_after_eat(philo);
	}
	return (NULL);
}
