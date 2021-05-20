#include <semaphore.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

static int	data;
static sem_t	*sem;

void	*f1(void *arg)
{
	int i, tmp;

	while (i < 50000)
	{
		sem_wait(sem);
		tmp = data;
		// sleep(1);
		data = tmp + 1;
		sem_post(sem);
		i++;
	}
	return (NULL);
}

void	*f2(void *arg)
{
	int i, tmp;

	i = 0;
	while (i < 50000)
	{
		sem_wait(sem);
		tmp = data;
		// sleep(1);
		data = tmp + 1;
		sem_post(sem);
		i++;
	}
	return (NULL);
}

int main(void)
{
	int		ret;
	pthread_t	thread1, thread2;

	/*
	sem = sem_open("/test", O_CREAT, 0777, 1);
	printf("%p\n", sem);
	printf("lock\n");
	sem_wait(sem);
	printf("after wait sem\n");
	sem_post(sem);
	*/
	data = 0;
	sem_unlink("/test");
	sem = sem_open("/test", O_CREAT, 0777, 5);
	if (pthread_create(&thread1, NULL, (void *)f1, NULL))
		return (1);
	if (pthread_create(&thread2, NULL, (void *)f2, NULL))
		return (1);
	if (pthread_join(thread1, NULL))
		return (1);
	if (pthread_join(thread2, NULL))
		return (1);
	printf("data: %d\n", data);
	sem_close(sem);
	sem_unlink("/test");
	return (0);
}


