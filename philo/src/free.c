/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:51:28 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/31 00:22:05 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_global *global)
{
	int		i;
	t_philo	*current;
	t_philo	*next;
	t_fork	*current1;
	t_fork	*next1;

	if (global->philo_num == 1)
	{
		free(global->philo->fork_left);
		free(global->philo);
		return ;
	}
	i = -1;
	current = global->philo;
	current1 = global->fork;
	while (++i < global->philo_num)
	{
		next = current->next;
		next1 = current1->next;
		free(current);
		free(current1);
		current = next;
		current1 = next1;
	}
}

void	emergency_free_fork(t_global *global)
{
	int		i;
	t_fork	*current;
	t_fork	*next;

	i = -1;
	current = global->fork;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	emergency_free_philo(t_global *global)
{
	int		i;
	t_philo	*current;
	t_philo	*next;
	t_fork	*last;

	i = -1;
	current = global->philo;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	last = ft_lstlast_fork(global->fork);
	last->next = NULL;
	emergency_free_fork(global);
}
