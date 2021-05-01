#include "philo_one.h"

void	*philo_work(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_nb % 2)
		usleep(2000);
	// printf("I'm No.%d thread\n", philo->philo_nb);
	(void)arg;
	return (NULL);
}
