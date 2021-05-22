#include <semaphore.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

static int	data;
static sem_t	*sem;

void	*f1(void *arg)
{
	int i, tmp;
	int *count;

	i = 0;
	count = (int *)arg;
	while (i < 50000)
	{
		// sem_wait(sem);
		tmp = *count;
		sleep(1);
		*count = tmp + 1;
		sem_post(sem);
		i++;
	}
	printf("%d %p\n", *count, count);
	return (NULL);
}

void	*f2(void *arg)
{
	int i, tmp;
	int	*count;

	i = 0;
	count = (int *)arg;
	while (i < 50000)
	{
		// sem_wait(sem);
		tmp = *count;
		sleep(1);
		*count = tmp + 1;
		sem_post(sem);
		i++;
	}
	printf("%d %p\n", *count, count);
	return (NULL);
}

int main(void)
{
	int		ret;
	int		pid;
	int		*count;
	pthread_t	thread1, thread2;

	/*
	sem = sem_open("/test", O_CREAT, 0777, 1);
	printf("%p\n", sem);
	printf("lock\n");
	sem_wait(sem);
	printf("after wait sem\n");
	sem_post(sem);
	*/
	count = (int *)malloc(sizeof(int));
	data = 0;
	sem_unlink("/test");
	sem = sem_open("/test", O_CREAT, 0777, 0);
	if ((pid = fork()) == -1)
	{
		printf("fork error\n");
	}
	else if (!pid)
	{
		f1(count);
		exit(0);
	}
	if ((pid = fork()) == -2)
	{
		printf("fork error\n");
	}
	else if (!pid)
	{
		f2(count);
		exit(0);
	}
	wait(NULL);
	wait(NULL);
	/*
	if (pthread_create(&thread1, NULL, (void *)f1, NULL))
		return (1);
	if (pthread_create(&thread2, NULL, (void *)f2, NULL))
		return (1);
	if (pthread_join(thread1, NULL))
		return (1);
	if (pthread_join(thread2, NULL))
		return (1);
	*/
	int val;
	val = 42;
	int c;

	c = 0;
	while (sem_trywait(sem) != -1)
	{
		c++;
	}
	printf("val:%d\n", c);
	printf("data: %d %p\n", *count, count);
	sem_close(sem);
	sem_unlink("/test");
	return (0);
}
