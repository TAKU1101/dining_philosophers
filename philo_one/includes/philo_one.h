#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

# define ERROR_PARAM_NUM		"The number of arguments should be 4-5."
# define ERROR_PARAM			"Invalid argument value"
# define ERROR_MALLOC			"Malloc failed."
# define ERROR_THREAD_CREATE	"thread create failed."
# define ERROR_THREAD_JOIN		"thread join failed."
# define ERROR_MUTEX_INIT		"mutex init failed."
# define ERROR_MUTEX_LOCK		"mutex lock failed."
# define ERROR_MUTEX_UNLOCK		"mutex unlock failed."
# define ERROR_MUTEX_DESTROY	"mutex destroy failed."

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
	pthread_mutex_t	let_mutex;
	int				*is_dead;
	pthread_mutex_t	*is_dead_mutex;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}					t_philo;

typedef struct s_info
{
	int				num_of_people;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				*is_dead;
	pthread_mutex_t	*is_dead_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_t		monitor;
}					t_info;

int					ft_atoi(const char *str);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					ft_isdigit(int c);
int					init_info(t_info *info, int argc, char *argv[]);
int					philo_exec(t_info *info);
void				*philo_work(void *arg);
int					philo_join(t_info *info);
int					error_log(char *err_msg);
int					philo_log(int nb, char *log);
long				get_time(void);
void				wait_time(long time);
int					free_info(t_info *info);
void				*monitor(void *arg);
int					check_param(t_info *info);

#endif
