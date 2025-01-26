/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_philo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:36:31 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/26 06:19:04 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_lstnew_philo(int content, t_global *global, t_fork *fork)
{
	t_philo	*lst;

	lst = malloc(sizeof(t_philo));
	if (!lst)
		return (NULL);
	lst->index = content;
	lst->global = global;
	lst->fork_right = fork->next;
	lst->fork_left = fork;
	lst->next = NULL;
	return (lst);
}

t_philo	*ft_lstlast_philo(t_philo *lst)
{
	int	i;

	i = 0;
	while (lst && lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_philo(t_philo **lst, t_philo *new)
{
	if (*lst)
		ft_lstlast_philo(*lst)->next = new;
	else
		*lst = new;
}
