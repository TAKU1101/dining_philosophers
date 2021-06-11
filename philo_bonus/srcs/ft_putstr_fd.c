#include "philo_three.h"

static void	ft_putchar_fd(char c, int fd)
{
	write(1, &c, fd);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		ft_putchar_fd(*(s++), fd);
}
