/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:52:12 by angela            #+#    #+#             */
/*   Updated: 2024/02/11 17:58:18 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h"

int	create_philos(t_main *main)
{
	int	i;
	int	j;

	main->philo = malloc(sizeof(t_philo) * (main->input.num_philo + 1));
	if (main->philo == NULL)
		return (FALSE);
	i = 0;
	j = 1;
	while (j < main->input.num_philo)
	{
		init_philo_struct(main, i, j);
		i++;
		j++;
	}
	j = 0;
	init_philo_struct(main, i, j);
	return (TRUE);
}

void	init_philo_struct(t_main *main, int i, int j)
{
	main->philo[i].id = i + 1;
	main->philo[i].num_of_times_ate = 0;
	main->philo[i].time_to_die = 0;
	main->philo[i].fork.left = i;
	main->philo[i].fork.right = j;
	main->philo[i].done = 0;
	main->philo[i].order = j;
	pthread_mutex_init(&main->philo[i].reset, NULL);
	pthread_mutex_init(&main->philo[i].ate, NULL);
}
