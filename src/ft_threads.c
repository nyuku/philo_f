/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:52:24 by angela            #+#    #+#             */
/*   Updated: 2024/02/11 17:52:25 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h"

int	create_threads(t_main *main)
{
	int	i;

	i = 0;
	main->philo_dead = FALSE;
	if (pthread_mutex_init(&main->write, NULL) != 0 \
		|| pthread_mutex_init(&main->index, NULL) != 0 \
		|| pthread_mutex_init(&main->dead, NULL) != 0)
		return (FALSE);
	main->t0 = get_time();
	while (i < main->input.num_philo)
	{
		pthread_mutex_lock(&main->index);
		main->n_thread = i;
		pthread_mutex_unlock(&main->index);
		if (pthread_create(&main->philo[i].thread,
				NULL, &routine, (void *) main) != 0)
			return (FALSE);
		i++;
		usleep(50);
	}
	if (pthread_create(&main->orchestrator, NULL, &checker, (void *) main) != 0)
		return (FALSE);
	if (join_threads(main) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	join_threads(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->input.num_philo)
	{
		if (pthread_join(main->philo[i].thread, NULL) != 0)
			return (FALSE);
		i++;
	}
	if (pthread_join(main->orchestrator, NULL) != 0)
		return (FALSE);
	return (TRUE);
}

int	destroy_threads(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->input.num_philo)
	{
		pthread_mutex_destroy(&main->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&main->write);
	return (TRUE);
}
