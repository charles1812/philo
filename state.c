#include "philo.h"

void	print_state(t_data *data, int nb, t_state state)
{
	static pthread_mutex_t	mut = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&mut);
	if (philo_is_running(data) || state == DIED)
		printf("%-8ld%d %s\n", timestamp(), nb, _philo_state(state));
	pthread_mutex_unlock(&mut);
}

int	philo_is_running(t_data *data)
{
	int	isrun;

	pthread_mutex_lock(&data->mis_running);
	isrun = data->is_running;
	pthread_mutex_unlock(&data->mis_running);
	return (isrun);
}