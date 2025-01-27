/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:32:09 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/27 02:42:49 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_setup(t_global *global)
{
	int		i;
	t_philo	*new;

	i = 0;
	while (++i < global->philo_num)
		global->fork = global->fork->next;
	global->philo = ft_lstnew_philo(1, global, global->fork);
	if (!global->philo)
		return (false);
	global->fork = global->fork->next;
	i = 1;
	if (global->philo_num > 1)
	{
		while (++i < global->philo_num + 1)
		{
			new = ft_lstnew_philo(i, global, global->fork);
			if (!new)
				return (emergency_free_philo(global), false);
			ft_lstadd_back_philo(&global->philo, new);
			global->fork = global->fork->next;
		}
	}
	return (true);
}

int	fork_setup(t_global *global)
{
	int		i;
	t_fork	*new;
	t_fork	*last;

	global->fork = ft_lstnew_fork(1, global);
	if (!global->fork)
		return (false);
	i = 1;
	if (global->philo_num > 1)
	{
		while (++i < global->philo_num + 1)
		{
			new = ft_lstnew_fork(i, global);
			if (!new)
				return (emergency_free_fork(global), false);
			ft_lstadd_back_fork(&global->fork, new);
		}
		last = ft_lstlast_fork(global->fork);
		last->next = global->fork;
	}
	return (true);
}

int	linked_setup(t_global *global)
{
	if (!fork_setup(global))
		return (false);
	if (!philo_setup(global))
		return (false);
	return (true);
}
