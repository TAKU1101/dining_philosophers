#include "philo_two.h"

char	*gen_name(int n)
{
	char	*number;
	char	*tmp;

	number = ft_itoa(n);
	if (number == NULL)
		return (NULL);
	tmp = ft_strjoin("/philo_two_let_", number);
	if (tmp == NULL)
		return (NULL);
	free(number);
	number = NULL;
	return (tmp);
}

sem_t	*sem_open_number(int n)
{
	sem_t	*sem;
	char	*name;

	name = gen_name(n);
	if (name == NULL)
		return (NULL);
	sem = sem_open(name, O_CREAT, 0600, 1);
	if (sem == NULL)
		return (NULL);
	free(name);
	name = NULL;
	return (sem);
}

int	sem_close_number(sem_t *sem, int n)
{
	char	*name;

	name = gen_name(n);
	if (name == NULL)
		return (error_log(ERROR_MALLOC));
	if (sem_close(sem) == -1)
		return (error_log(ERROR_SEM_CLOSE));
	if (sem_unlink(name) == -1)
		return (error_log(ERROR_SEM_UNLINK));
	free(name);
	name = NULL;
	return (0);
}
