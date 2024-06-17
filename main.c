#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		print_help();
	parse(&data, ac, av);
	init(&data);
	ft_process(&data);
	philo_destroy(&data);
	return (EXIT_SUCCESS);
}
