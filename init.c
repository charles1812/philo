#include "philo.h"

time_t	timestamp(void)
{
	static time_t	initime;
	struct timeval	t;

    initime = -1;
	gettimeofday(&t, NULL);
	if (initime == -1)
		initime = (t.tv_sec * 1000 + t.tv_usec / 1000);
	return ((t.tv_sec * 1000 + t.tv_usec / 1000) - initime);
}

static void	_philo_init_philos(t_data *data)
{
	int	    i;

	i = 0;
	while (i < data->nb)
	{
		data->philos[i].r_fork = &data->forks[(i + 1) % data->nb];
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].id = k;
		data->philos[i].last_eat = 0;
		data->philos[i].nb_ate = 0;
		data->philos[i].data = data;
		data->philos[i].thread_id = 0;
		if (pthread_mutex_init(&data->philos[i].eating, NULL)
			|| pthread_mutex_init(&data->philos[i].eaten, NULL))
			print_error(data, "Mutex init error");
		data->philos[i++].dead = 0;
	}
}

void    init_forks(t_data *data)
{
    int     i;

    i = 0;
    while (i < data->nb)
    {
        if (pthread_mutex_init(&data->forks[i++], NULL))
			break ;
    }
    if (i != data->nb)
    {
		while (i-- != 0)
			pthread_mutex_destroy(&data->forks[i]);
    }
}

void    init(t_data *data)
{
    data->forks = malloc(sizeof(*data->forks) * data->nb);
    if (!data->forks)
        print_error(data, "bad forks alloc");
    init_forks(data);
    data->philos = malloc(sizeof(data->philos) * data->nb);
    if(!data->philos)
        print_error(data, "bad philo alloc");
    init_philos(data);
    timestamp();
}