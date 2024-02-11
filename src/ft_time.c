/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:52:30 by angela            #+#    #+#             */
/*   Updated: 2024/02/11 17:52:31 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long long	delta_time(long long time)
{
	if (time > 0)
		return (get_time() - time);
	return (0);
}

int	find_delta(struct timeval t1, struct timeval t2)
{
	int	start;
	int	end;

	start = (int)(t1.tv_sec * 1000 + t1.tv_usec / 1000);
	end = (int)(t2.tv_sec * 1000 + t2.tv_usec / 1000);
	return (end - start);
}

void	exec_action(long long time)
{
	struct timeval	t1;
	struct timeval	t2;
	int				delta;

	delta = 0;
	gettimeofday(&t1, NULL);
	while (delta < time)
	{
		usleep(100);
		gettimeofday(&t2, NULL);
		delta = find_delta(t1, t2);
	}
}
