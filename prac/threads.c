#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/*
** pthread_create
** pthread_detach
** pthread_join
*/

void	f1(void);
void	f2(void);

static int data;

int main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;
	int			ret1;
	int			ret2;

	ret1 = pthread_create(&thread1, NULL, (void *)f1, NULL);
	ret2 = pthread_create(&thread2, NULL, (void *)f2, NULL);
	data = 0;
	if (ret1)
	{
		puts("thread1 create error");
	}
	else if (ret2)
	{
		puts("thread2 create error");
	}
	puts("thread1 join");
	printf("before join: %d\n", data);
	// ret1 = pthread_join(thread1, NULL);
	ret1 = pthread_detach(thread1);
	if (ret1)
	{
		puts("thread1 join error");
	}
	puts("thread2 join");
	// ret2 = pthread_join(thread2, NULL);
	ret2 = pthread_detach(thread2);
	if (ret2)
	{
		printf("ret2: %d\n", ret2);
		puts("thread2 join error");
	}
	printf("after join: %d\n", data);
	puts("done");
	return (0);
}

void	f1(void)
{
	int i;

	i = 0;
	while (i < 8)
	{
		data++;
		puts("Doing f1");
		usleep(20);
		i++;
	}
	return ;
}

void	f2(void)
{
	int i;

	i = 0;
	while (i < 8)
	{
		puts("Doing f2");
		printf("in f2: %d\n", data);
		usleep(1);
		i++;
	}
	return ;
}
