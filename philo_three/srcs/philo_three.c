#include "philo_three.h"

int	main(int argc, char *argv[])
{
	t_info	info;

	if (init_info(&info, argc, argv))
		return (1);
	if (philo_exec(&info))
		return (1);
	(void)argc;
	(void)argv;
	return (0);
}
