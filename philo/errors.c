#include "philo.h"

void	print_help(void)
{
	printf("Usage: ./philo <number_of_philosophers> <time_to_die> ");
	printf("<time_to_eat> <time_to_sleep> ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
	exit(EXIT_SUCCESS);
}

void	print_error(t_data *data, const char *s)
{
	philo_destroy(data);
	printf("%s: %s\n", data->pn, s);
	exit(EXIT_FAILURE);
}
