/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_forks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:52:05 by angela            #+#    #+#             */
/*   Updated: 2024/02/11 17:52:06 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h"

int	create_forks(t_main *main)
{
	int	i;

	main->forks = malloc(sizeof(pthread_mutex_t) * main->input.num_philo + 1);
	if (main->forks == NULL)
		return (FALSE);
	i = 0;
	while (i < main->input.num_philo)
	{
		if (pthread_mutex_init(&main->forks[i], NULL) != 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	unlock_forks(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->input.num_philo)
	{
		pthread_mutex_unlock(&main->forks[i]);
		i++;
	}
}
