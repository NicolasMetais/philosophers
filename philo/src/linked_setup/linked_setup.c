/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:32:09 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/27 00:35:41 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_setup(t_global *global)
{
	int	i;

	i = 0;
	while (++i < global->philo_num)
		global->fork = global->fork->next;
	global->philo = ft_lstnew_philo(1, global, global->fork);
	global->fork = global->fork->next;
	i = 1;
	if (global->philo_num > 1)
	{
		while (++i < global->philo_num + 1)
		{
			ft_lstadd_back_philo(&global->philo,
				ft_lstnew_philo(i, global, global->fork));
			global->fork = global->fork->next;
		}
	}
}

void	fork_setup(t_global *global)
{
	int		i;
	t_fork	*last;

	global->fork = ft_lstnew_fork(1, global);
	i = 1;
	if (global->philo_num > 1)
	{
		while (++i < global->philo_num + 1)
			ft_lstadd_back_fork(&global->fork, ft_lstnew_fork(i, global));
		last = ft_lstlast_fork(global->fork);
		last->next = global->fork;
	}
}

void	linked_setup(t_global *global)
{
	fork_setup(global);
	philo_setup(global);
}
