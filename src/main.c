/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:52:44 by angela            #+#    #+#             */
/*   Updated: 2024/02/11 18:11:24 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h"

int	main(int argc, char **argv)
{
	t_main	main;

	if (ft_errors(argc, argv, &main) == FALSE)
		return (1);
	if (create_philos(&main) == FALSE)
		return (2);
	if (create_forks(&main) == FALSE)
		return (3);
	if (main.input.num_philo == 1)
	{
		if (one_philo(&main) == FALSE)
			return (4);
		return (0);
	}
	printf("\nTime(ms) Philo\tAction\t\n");
	printf("--------------------------------------------------------\n");
	if (create_threads(&main) == FALSE)
		return (5);
	if (destroy_threads(&main) == FALSE)
		return (6);
	ft_free(&main);
	return (0);
}

int	one_philo(t_main *main)
{
	if (pthread_mutex_init(&main->write, NULL) != 0)
		return (FALSE);
	main->t0 = get_time();
	philo_print(main, 1, FORK);
	exec_action(main->input.time_to_die);
	philo_print(main, 1, DIED);
	ft_free(main);
	return (TRUE);
}
