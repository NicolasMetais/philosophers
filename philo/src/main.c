/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 03:29:41 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/26 00:11:44 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_boolean	global_init(t_global *global, char **av)
{
	int	i;

	i = -1;
	global->philo_num = ft_atol(av[1]);
	global->die_timer = ft_atol(av[2]);
	global->eat_timer = ft_atol(av[3]);
	global->sleep_timer = ft_atol(av[4]);
	global->kill = false;
	global->death_check = malloc(sizeof(long)
			* (global->philo_num + 1));
	if (!global->death_check)
		return (false);
	while (++i < global->philo_num + 1)
		global->death_check[i] = 0;
	global->elapsed = 0;
	return (true);
}


void	philo_setup(t_global *global)
{
	int		i;
	t_fork	*last;

	global->fork = ft_lstnew_fork(1, global);
	i = 1;
	if (global->philo_num > 1)
	{
		while (++i < global->philo_num + 1)
			ft_lstadd_back_fork(&global->fork, ft_lstnew_fork(1, global));
		last = ft_lstlast_fork(global->fork);
		last->next = global->fork;
	}
	global->philo = ft_lstnew_philo(1, global);
	i = 1;
	if (global->philo_num > 1)
	{
		while (++i < global->philo_num + 1)
			ft_lstadd_back_philo(&global->philo, ft_lstnew_philo(i, global));
	}
}


int	main(int ac, char **av)
{
	t_global	global;

	if (ac == 5)
	{
		if (!parse_args(av))
			return (false);
		if (!global_init(&global, av))
			return (false);
		philo_setup(&global);
		boring_life_setup(&global);
	}
}
