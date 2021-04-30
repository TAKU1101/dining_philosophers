#include "philo_one.h"

void	*philo_work(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("I'm No.%d thread\n", philo->philo_nb);
	(void)arg;
	return (NULL);
}
