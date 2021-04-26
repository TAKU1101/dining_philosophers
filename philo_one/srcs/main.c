#include "philo_one.h"

int	init_philos(int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		i++;
	}
	return (0);
}

int	init_info(t_info *info, int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (1);
	info->num_of_people = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->must_eat = -1;
	if (argc == 6)
	{
		info->must_eat = ft_atoi(argv[5]);
		if (info->must_eat < 0)
			return (1);
	}
	return (0);
}

int main(int argc, char *argv[])
{
	t_info	info;

	if (init_info(&info, argc, argv))
		return (1);
	(void)argc;
	(void)argv;
	return (0);
}
