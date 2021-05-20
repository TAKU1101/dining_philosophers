#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>

# define ERROR_PARAM_NUM		"The number of arguments should be 4-5."
# define ERROR_PARAM			"Invalid argument value"
# define ERROR_MALLOC			"Malloc failed."
# define ERROR_THREAD_CREATE	"thread create failed."
# define ERROR_THREAD_JOIN		"thread join failed."
# define ERROR_SEM_OPEN			"semaphore open failed."
# define ERROR_SEM_CLOSE		"semaphore close failed."
# define ERROR_SEM_POST			"semaphore post failed."
# define ERROR_SEM_WAIT			"semaphore wait failed."
# define ERROR_SEM_UNLINK		"semaphore unlink failed."

# define LOG_TAKEEN		"has taken a fork"
# define LOG_EATING		"is eating"
# define LOG_SLEEPING	"is sleeping"
# define LOG_THINKING	"is thinking"
# define LOG_DIED		"is died"

typedef struct s_philo
{
	int				philo_nb;
	int				eat_nb;
	int				num_of_people;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
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

int					ft_atoi(const char *str);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					ft_isdigit(int c);
char				*ft_itoa(int n);
char				*ft_strjoin(char const *s1, char const *s2);
int					init_info(t_info *info, int argc, char *argv[]);
int					error_log(char *msg);
long				get_time(void);
void				wait_time(long time);
int					philo_log(int nb, char *log);
int					check_param(t_info *info);
sem_t				*sem_open_number(int n);
int					sem_close_number(sem_t *sem, int n);

#endif
