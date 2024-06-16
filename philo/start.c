#include "philo.h"

void	*philo_routine(void *p)
{
	t_philo *const	philo;
	t_data *const	data;

    philo = p;
    data = philo->data;
	if (philo->id % 2)
		custom_sleep(philo, 4);
	while (philo_is_running(data))
	{
		philo_eat(philo);
		if (!philo_is_running(philo->data))
			break ;
		print_state(data, philo->id, SLEEPING);
		custom_sleep(philo, data->t_tosleep);
		print_state(data, philo->id, THINKING);
	}
	return (NULL);
}

void    philo_start(t_data *data)
{
    int     i;

    i = 0;
    data->is_running = 1;
    while (i < data->nb)
    {
        data->philos[i].last_eat = timetsamp();
        if (pthread_create(&data->philos[i].thread_id, NULL,
				philo_routine, &data->philos[i]))
    }
}