#include "philo.h"

void    take_r_fork(t_philo *philo)
{
    pthread_mutex_lock(philo->r_fork);
	print_state(philo->data, philo->id, FORK_TAKEN);
}

void    take_l_fork(t_philo *philo)
{
    pthread_mutex_lock(philo->l_fork);
	print_state(philo->data, philo->id, FORK_TAKEN);
}

void    philo_take_forks(t_philo *philo)
{
    if(philo->id % 2)
    {
        take_r_fork(philo);
        take_l_pork(philo);
    }
    else
	{
		take_l_fork(philo);
		if (philo->l_fork != philo->r_fork)
			take_r_fork(philo);
	}
}

int	philo_is_running(t_data *data)
{
	int	isrun;

	pthread_mutex_lock(&data->mis_running);
	isrun = data->is_running;
	pthread_mutex_unlock(&data->mis_running);
	return (isrun);
}

void    philo_eat(t_philo *philo)
{
    philo_take_forks(philo);
    if(philo->r_fork == philo->l_fork)
	{
		while (philo_is_running(philo->data))
			usleep(50);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(&philo->eating);
	print_state(philo->data, philo->id, EATING);
	philo->last_eat = timestamp();
	pthread_mutex_unlock(&philo->eating);
	custom_sleep(philo, ((t_data *)philo->data)->t_toeat);
	pthread_mutex_lock(&philo->eaten);
	++philo->nb_ate;
	pthread_mutex_unlock(&philo->eaten);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}




	
	