#include "philo_two.h"

static int	int_len(int n)
{
	int		count;
	long	long_n;

	count = 0;
	long_n = n;
	if (long_n == 0)
		return (1);
	if (long_n < 0)
	{
		count++;
		long_n = long_n * -1;
	}
	while (long_n)
	{
		long_n = long_n / 10;
		count++;
	}
	return (count);
}

static char	*set_num(long num, char *s)
{
	int	n;

	n = num % 10;
	if (num)
	{
		s = set_num(num / 10, s);
		*s = '0' + n;
		s++;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	int		len;
	long	long_n;
	char	*num;
	char	*p;

	len = int_len(n);
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (!num)
		return (0);
	p = num;
	num[len] = '\0';
	long_n = n;
	if (long_n == 0)
		num[0] = '0';
	if (n < 0)
	{
		*num = '-';
		num++;
		long_n = long_n * -1;
	}
	set_num(long_n, num);
	return (p);
}
