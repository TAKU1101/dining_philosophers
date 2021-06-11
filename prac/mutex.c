#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

/*
** pthread_mutex_init
** pthread_mutex_destroy
** pthread_mutex_lock
** pthread_mutex_unlock
*/

void	f1(void);
void	f2(void);

static int				counter = 0;
static int				loop_max = 10000;
static pthread_mutex_t	m;

int main(void)
{
	pthread_t thread1;
	pthread_t thread2;
	int ret1;
	int ret2;

	ret1 = pthread_create(&thread1, NULL, (void *)f1, NULL);
	ret2 = pthread_create(&thread2, NULL, (void *)f2, NULL);
	pthread_mutex_init(&m, NULL);
	if (ret1)
		puts("thread1 create error");
	if (ret2)
		puts("thread2 create error");
	puts("join thread1");
	ret1 = pthread_join(thread1, NULL);
	if (ret1)
		puts("thread1 join error");
	ret2 = pthread_join(thread2, NULL);
	if (ret2)
		puts("thread2 join error");
	printf("counter: %d\n", counter);
	puts("done");
	pthread_mutex_destroy(&m);
	return (0);
}

void	f1(void)
{
	int i, tmp;

	i = 0;
	while (i < loop_max)
	{
#ifndef NOLOCK
		int r;
		if ((r = pthread_mutex_lock(&m)) != 0)
			puts("lock error");
#endif
		// tmp = counter; // f1: tmp: 0 f2: tmp: 0
		// tmp = tmp + 1; // f1: tmp: 1 f2: tmp: 1
		// counter = tmp; // counter: 1
		counter++;
#ifndef NOLOCK
		if ((r = pthread_mutex_unlock(&m)) != 0)
			puts("unlock error");
#endif
		i++;
	}
	return ;
}

void	f2(void)
{
	int i;

	i = 0;
	while (i < loop_max)
	{
#ifndef NOLOCK
		int r;
		if ((r = pthread_mutex_lock(&m)) != 0)
			puts("lock error");
#endif
		counter++;
#ifndef NOLOCK
		if ((r = pthread_mutex_unlock(&m)) != 0)
			puts("unlock error");
#endif
		i++;
	}
	return ;
}
