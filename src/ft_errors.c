/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:51:58 by angela            #+#    #+#             */
/*   Updated: 2024/02/11 17:52:00 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h"

int	ft_errors(int argc, char **argv, t_main *main)
{
	if (argc == 2 && !ft_strncmp(argv[1], "help", 4)
		&& ft_strlen(argv[1]) == 4)
	{
		printf("%s\n", HELP);
		return (FALSE);
	}
	else if (init_input_struct(argc, argv, main) == FALSE)
	{
		printf("%s\n", "ERROR: The number of argments must be 4 or 5");
		return (FALSE);
	}
	else
	{
		print_args_errors(main, argc);
		if (!main->input.num_philo || !main->input.time_to_die
			|| !main->input.time_to_eat || !main->input.time_to_sleep
			|| (argc == 6 && !main->input.num_of_times_eat))
			return (FALSE);
	}
	return (TRUE);
}

int	init_input_struct(int argc, char **argv, t_main *main)
{
	if (argc == 5 || argc == 6)
	{
		main->input.num_philo = ft_atoi(argv[1]);
		main->input.time_to_die = ft_atoi(argv[2]);
		main->input.time_to_eat = ft_atoi(argv[3]);
		main->input.time_to_sleep = ft_atoi(argv[4]);
		main->philo_ate = 0;
		if (argc == 6)
			main->input.num_of_times_eat = ft_atoi(argv[5]);
		else
			main->input.num_of_times_eat = -1;
		return (TRUE);
	}
	return (FALSE);
}

void	print_args_errors(t_main *main, int argc)
{
	if (!main->input.num_philo)
		printf("%s\n", "ERROR: There is a mistake in number of philosophers");
	if (!main->input.time_to_die)
		printf("%s\n", "ERROR: There is a mistake in time to die");
	if (!main->input.time_to_eat)
		printf("%s\n", "ERROR: There is a mistake in time to eat");
	if (!main->input.time_to_sleep)
		printf("%s\n", "ERROR: There is a mistake in time to sleep");
	if (argc == 6 && !main->input.num_of_times_eat)
		printf("%s\n", "ERROR: There is a mistake in number of times each \
			philosopher must eat");
}
