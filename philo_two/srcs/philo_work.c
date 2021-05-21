#include "philo_two.h"

void	*philo_work(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("I'm %d\n", philo->philo_nb);
	return (NULL);
}
