#include "philo_one.h"

void	*philo_work(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_nb % 2)
		usleep(20000);
	// printf("I'm No.%d thread\n", philo->philo_nb);
	philo_log(philo->philo_nb, LOG_TAKEEN);
	return (NULL);
}
