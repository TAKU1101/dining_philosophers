#include "philo_three.h"

static void	ft_putchar_fd(char c, int fd)
{
	write(1, &c, fd);
}

static void	put_num(unsigned long num, int fd)
{
	unsigned long n;

	n = num % 10;
	if (num)
	{
		put_num(num / 10, fd);
		ft_putchar_fd('0' + n, fd);
	}
}

void		ft_putnbr_fd(unsigned long n, int fd)
{
	if (n == 0)
		ft_putchar_fd('0', fd);
	put_num(n, fd);
}
