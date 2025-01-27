/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 03:29:41 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/27 17:25:46 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_arg_six(t_global *global, char **av, int ac)
{
	if (ac == 6)
	{
		pthread_mutex_init(&global->count, NULL);
		global->max_diet = ft_atol(av[5]);
		global->diet = true;
	}
	else
		global->diet = false;
}

t_boolean	global_init(t_global *global, char **av, int ac)
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
		return (free_all(global), false);
	global->eat_count = ft_calloc(sizeof(long),
			(global->philo_num + 1));
	if (!global->eat_count)
		return (free_all(global), free(global->death_check), false);
	while (++i < global->philo_num + 1)
		global->death_check[i] = 0;
	global->elapsed = 0;
	is_arg_six(global, av, ac);
	return (true);
}

void	mutex_destroy(t_global	*global, int ac)
{
	int	i;

	pthread_mutex_destroy(&global->timer);
	pthread_mutex_destroy(&global->death);
	pthread_mutex_destroy(&global->exit);
	if (ac == 6)
		pthread_mutex_destroy(&global->count);
	i = -1;
	if (global->philo_num > 1)
	{
		while (++i < (int)global->philo_num)
		{
			pthread_mutex_destroy(&global->fork->num);
			global->fork = global->fork->next;
		}
	}
}

int	main(int ac, char **av)
{
	t_global	global;

	if (ac == 5 || ac == 6)
	{
		if (!parse_args(av))
			return (false);
		if (!global_init(&global, av, ac))
			return (false);
		if (!linked_setup(&global))
			return (false);
		pthread_mutex_init(&global.timer, NULL);
		pthread_mutex_init(&global.death, NULL);
		pthread_mutex_init(&global.exit, NULL);
		if (!boring_life_setup(&global))
			return (false);
		mutex_destroy(&global, ac);
		free(global.death_check);
		free(global.eat_count);
		free_all(&global);
	}
}
