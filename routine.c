#include "philo.h"


static void	wait_thread(t_data *data)
{
	size_t	k;

	k = 0;
	while (k < data->nb)
	{
		if (data->philos[k].thread_id != 0)
			pthread_join(data->philos[k].thread_id, NULL);
		++k;
	}
}

void	*ft_routine(void *p)
{
	t_philo *const		philo;
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

void	ft_process(t_data *data)
{
	size_t	k;

	data->is_running = 1;
	k = 0;
	while (k < data->nb)
	{
		data->philos[k].last_eat = timestamp();
		if (pthread_create(&data->philos[k].thread_id, NULL,
				ft_routine, &data->philos[k]))
		{
			wait_thread(data);
			print_error(data, "Thread init error");
		}
		usleep(500);
		++k;
	}

}