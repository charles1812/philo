#include "philo.h"

void	philo_destroy(t_data *data)
{
	size_t	k;

	if (data->forks != NULL)
	{
		k = 0;
		while (k < data->nb)
			pthread_mutex_destroy(&data->forks[k++]);
		free(data->forks);
	}
	if (data->philos != NULL)
	{
		k = 0;
		while (k < data->nb)
		{
			pthread_mutex_destroy(&data->philos[k].eating);
			pthread_mutex_destroy(&data->philos[k].eaten);
			++k;
		}
		free(data->philos);
	}
	pthread_mutex_destroy(&data->mis_running);
}
