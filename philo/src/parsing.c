/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 23:27:46 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/22 19:30:43 by nmetais          ###   ########.fr       */
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
	while (i < 5)
	{
		if (!digit_check(av[i]))
			return (false);
		if (ft_atol(av[i]) > INT_MAX || ft_atol(av[i]) < INT_MIN)
		{
			write(2, "int overflow", 12);
			return (false);
		}
		i++;
	}
	return (true);
}
