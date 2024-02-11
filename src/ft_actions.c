/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:51:50 by angela            #+#    #+#             */
/*   Updated: 2024/02/11 17:51:52 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h"

int	philo_eat(t_main *main, int i)
{
	if (i % 2 == 0)
		usleep(150);
	if (pthread_mutex_lock(&main->forks[main->philo[i].fork.right]) != 0)
		return (FALSE);
	if (philo_print(main, main->philo[i].id, FORK) == FALSE)
	{
		pthread_mutex_unlock(&main->forks[main->philo[i].fork.right]);
		return (FALSE);
	}
	if (pthread_mutex_lock(&main->forks[main->philo[i].fork.left]) != 0)
		return (FALSE);
	if (philo_print(main, main->philo[i].id, FORK) == FALSE \
		|| philo_print(main, main->philo[i].id, EAT) == FALSE)
	{
		drop_forks(main, i);
		return (FALSE);
	}
	pthread_mutex_lock(&main->philo[i].reset);
	main->philo[i].time_to_die = get_time();
	pthread_mutex_unlock(&main->philo[i].reset);
	exec_action(main->input.time_to_eat);
	drop_forks(main, i);
	return (TRUE);
}

int	philo_sleep(t_main *main, int i)
{
	if (philo_print(main, main->philo[i].id, SLEEP) == FALSE)
		return (FALSE);
	exec_action(main->input.time_to_sleep);
	return (TRUE);
}

int	philo_think(t_main *main, int i)
{
	if (philo_print(main, main->philo[i].id, THINK) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	philo_is_dead(t_main *main, int *i)
{
	int	time;

	if (*i == main->input.num_philo)
		*i = 0;
	pthread_mutex_lock(&main->philo[*i].reset);
	time = delta_time(main->philo[*i].time_to_die);
	pthread_mutex_unlock(&main->philo[*i].reset);
	if (time > main->input.time_to_die)
	{
		philo_print(main, main->philo[*i].id, DIED);
		pthread_mutex_lock(&main->dead);
		main->philo_dead = TRUE;
		pthread_mutex_unlock(&main->dead);
		return (TRUE);
	}
	i++;
	return (FALSE);
}

int	drop_forks(t_main *main, int i)
{
	if (pthread_mutex_unlock(&main->forks[main->philo[i].fork.left]))
		return (FALSE);
	if (pthread_mutex_unlock(&main->forks[main->philo[i].fork.right]))
		return (FALSE);
	main->philo[i].num_of_times_ate++;
	return (TRUE);
}
