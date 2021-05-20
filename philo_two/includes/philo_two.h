#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct s_philo
{
	int				philo_nb;
	int				eat_nb;
	int				num_of_people;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_t		thread;
	long			last_eat_time;
	sem_t			*let_bsem;
	int				*is_dead;
	sem_t			*is_dead_bsem;
	sem_t			*fork_sem;
}					t_philo;

typedef struct s_info
{
	int				num_of_people;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				*is_dead;
	sem_t			*is_dead_bsem;
	sem_t			*fork_sem;
	t_philo			*philos;
	pthread_t		monitor;
}					t_info;

#endif
