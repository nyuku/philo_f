/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:52:18 by angela            #+#    #+#             */
/*   Updated: 2024/02/11 18:09:44 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h"

void	*routine(void *args)
{
	t_main	*main;
	int		i;

	main = (t_main *)args;
	pthread_mutex_lock(&main->index);
	i = main->n_thread;
	pthread_mutex_unlock(&main->index);
	while (main->input.num_of_times_eat > 0 \
		&& main->input.num_of_times_eat > main->philo[i].num_of_times_ate \
		&& main->philo_dead == FALSE)
		routine_execute(main, i);
	while (main->input.num_of_times_eat < 0)
	{
		pthread_mutex_lock(&main->dead);
		if (main->philo_dead == TRUE)
		{
			pthread_mutex_unlock(&main->dead);
			break ;
		}
		pthread_mutex_unlock(&main->dead);
		if (routine_execute(main, i) == FALSE)
			break ;
	}
	return (NULL);
}

int	routine_execute(t_main *main, int i)
{
	if (philo_eat(main, i) == FALSE)
		return (FALSE);
	if (main->philo[i].num_of_times_ate >= main->input.num_of_times_eat)
	{
		pthread_mutex_lock(&main->philo[i].ate);
		main->philo[i].done++;
		pthread_mutex_unlock(&main->philo[i].ate);
	}
	if (main->input.num_of_times_eat != main->philo[i].num_of_times_ate)
	{
		if (philo_sleep(main, i) == FALSE)
			return (FALSE);
		if (philo_think(main, i) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

void	*checker(void *args)
{
	t_main	*main;
	int		i;

	main = (t_main *)args;
	i = 0;
	while (main->input.num_of_times_eat > 0 && main->philo_dead == FALSE)
	{
		pthread_mutex_lock(&main->philo[i].ate);
		if (main->philo[i].done)
		{
			pthread_mutex_unlock(&main->philo[i].ate);
			break ;
		}
		pthread_mutex_unlock(&main->philo[i].ate);
		if (philo_is_dead(main, &i) == TRUE)
			break ;
		usleep(25);
	}
	while (main->input.num_of_times_eat < 0 && main->philo_dead == FALSE)
	{
		if (philo_is_dead(main, &i) == TRUE)
			break ;
	}
	return (NULL);
}

int	philo_print(t_main *main, int id, char *status)
{
	long long	now;

	now = delta_time(main->t0);
	pthread_mutex_lock(&main->write);
	pthread_mutex_lock(&main->dead);
	if (main->philo_dead == TRUE)
	{
		pthread_mutex_unlock(&main->write);
		pthread_mutex_unlock(&main->dead);
		return (FALSE);
	}
	pthread_mutex_unlock(&main->dead);
	printf("%-10lld %s%-3d %-30s\n" COLOR_RESET, now, get_philo_color(id),id, status);
	pthread_mutex_unlock(&main->write);
	return (TRUE);
}
