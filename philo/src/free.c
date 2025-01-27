/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:51:28 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/27 00:59:41 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free(t_global *global)
{
	int		i;
	t_philo	*current;
	t_philo	*next;
	t_fork	*current1;
	t_fork	*next1;

	i = -1;
	while (++i < global->philo_num)
	{
		
	}
}

/* void	free_pile(t_sort *sort)
{
	t_list	*current;
	t_list	*next;
	size_t	i;

	i = 0;
	current = sort->pilea;
	while (i < sort->lena)
	{
		next = current->next;
		free(current);
		current = next;
		i++;
	}
} */
