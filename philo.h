#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

# define ERR_BAD_ALLOC 1

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	int				dead;
	unsigned int	nb_ate;
	void			*data;
	time_t			last_eat;
	pthread_mutex_t	eating;
	pthread_mutex_t	eaten;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}				t_philo;

typedef struct s_data
{
	char			*pn;
	unsigned int	nb;
	int				is_running;
	pthread_mutex_t	mis_running;
	time_t			t_todie;
	time_t			t_toeat;
	time_t			t_tosleep;
	unsigned int	t_toeach;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}				t_data;

/* PARSE */

void			parse(t_data *data, int argc, char **argv);

/* PHILO */

void			init(t_data *data);
void			philo_destroy(t_data *data);
void			print_help(void);
void			print_error(t_data *data, const char *s);

/* LOG */

typedef enum e_state
{
	FORK_TAKEN,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}				t_state;


#endif