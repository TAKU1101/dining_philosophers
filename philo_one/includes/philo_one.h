#ifndef PHILO_ONE
# define PHILO_ONE

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t		thread;
	long			last_eat_time;
}					t_philo;

typedef struct s_monitor
{
	pthread_mutex_t	monitor;
}					t_monitor;

typedef struct s_info
{
	int				num_of_people;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	t_monitor		monitor;
}					t_info;

int					ft_atoi(const char *str);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					ft_isdigit(int c);

#endif
