/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:52:36 by angela            #+#    #+#             */
/*   Updated: 2024/02/11 17:53:46 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h"

int	ft_atoi(char *str)
{
	int			i;
	long int	n;

	i = 0;
	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	if (n < 0 || ((str[i] < '0' || str[i] > '9') && str[i] != '\0')
		|| n > INT_MAX)
		return (0);
	return (n);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while ((str1[i] || str2[i]) && i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

int	ft_strlen(const char *str)
{
	int	size;

	size = 0;
	while (str[size] != '\0')
	{
		size++;
	}
	return (size);
}

void	ft_free(t_main *main)
{
	free(main->philo);
	free(main->forks);
}

const char* get_philo_color(int color_index) 
{
   
    if (color_index == 5) return COLOR_ROSE;
    if (color_index == 1) return COLOR_LILAC;
    if (color_index == 2) return COLOR_VIOLET;
    if (color_index == 3) return COLOR_GREEN;
    if (color_index == 4) return COLOR_CYAN;

    return COLOR_RESET; // Sécurité, ne devrait pas arriver
}

