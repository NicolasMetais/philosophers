/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 23:27:46 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/27 17:25:07 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_boolean	digit_check(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			if (str[i] == '-')
			{
				write(2, "i only need positiv numbers", 27);
				return (false);
			}
			write(2, "not a numbers", 13);
			return (false);
		}
		i++;
	}
	return (true);
}

t_boolean	parse_args(char **av)
{
	size_t	i;

	i = 1;
	while (av[i])
	{
		if (!digit_check(av[i]))
			return (false);
		if (ft_atol(av[i]) > INT_MAX)
		{
			write(2, "int overflow", 12);
			return (false);
		}
		if (ft_atol(av[i]) <= 0)
		{
			write(2, "only positiv numbers", 20);
			return (false);
		}
		i++;
	}
	return (true);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	char	*al;

	i = 0;
	if (nmemb * size > 2147483647)
		return (NULL);
	al = malloc(nmemb * size);
	if (al == NULL)
		return (NULL);
	while (i < (nmemb * size))
	{
		al[i] = 0;
		i++;
	}
	return ((void *)al);
}
