#include "philo_one.h"

int	main(int argc, char *argv[])
{
	t_info	info;

	if (init_info(&info, argc, argv))
		return (1);
	printf("test\n");
	if (philo_exec(&info))
		return (1);
	if (philo_join(&info))
		return (1);
	if (free_info(&info))
		return (1);
	return (0);
}
