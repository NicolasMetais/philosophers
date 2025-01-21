/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 03:29:41 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/21 21:55:16 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init(t_philo *philo, char **av)
{
	philo->philo_num = ft_atol(av[1]);
	philo->die_timer = ft_atol(av[2]);
	philo->eat_timer = ft_atol(av[3]);
	philo->sleep_timer = ft_atol(av[4]);
}

int	main(int ac, char **av)
{
	t_philo	philo;

	(void)philo;
	if (ac == 5)
	{
		if (!parse_args(av))
			return (false);
		philo_init(&philo, av);
		boring_life_setup(&philo);
	}
}
