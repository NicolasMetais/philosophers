/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 03:29:41 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/25 05:29:45 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	global_init(t_global *global, char **av)
{
	global->philo_num = ft_atol(av[1]);
	global->die_timer = ft_atol(av[2]);
	global->eat_timer = ft_atol(av[3]);
	global->sleep_timer = ft_atol(av[4]);
	global->elapsed = 0;
}


void	philo_setup(t_global *global)
{
	int	i;

	global->philo = ft_lstnew(1, global);
	i = 2;
	if (global->philo_num > 1)
	{
		while (i < global->philo_num + 1)
		{
			ft_lstadd_back(&global->philo, ft_lstnew(i, global));
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	t_global	global;

	if (ac == 5)
	{
		if (!parse_args(av))
			return (false);
		global_init(&global, av);
		philo_setup(&global);
/* 		while (global.philo)
		{
			printf("%d\n", global.philo->index);
			global.philo = global.philo->next;
		} */
		boring_life_setup(&global);
	}
}
