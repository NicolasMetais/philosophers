/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 03:29:41 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/27 02:00:25 by nmetais          ###   ########.fr       */
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

void	mutex_init(t_global *global)
{
	pthread_mutex_init(&global->timer, NULL);
	pthread_mutex_init(&global->death, NULL);
	pthread_mutex_init(&global->exit, NULL);
}

void	mutex_destroy(t_global	*global)
{
	int	i;

	pthread_mutex_destroy(&global->timer);
	pthread_mutex_destroy(&global->death);
	pthread_mutex_init(&global->exit, NULL);
	i = -1;
	while (++i < (int)global->philo_num)
	{
		pthread_mutex_destroy(&global->fork->num);
		global->fork = global->fork->next;
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
		if (!linked_setup(&global))
			return (false);
		mutex_init(&global);
		if (!boring_life_setup(&global))
			return (false);
		mutex_destroy(&global);
		free(global.death_check);
		free_all(&global);
	}
}
