/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_fork.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:58:38 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/31 00:24:53 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*ft_lstnew_fork(int content, t_global *global)
{
	t_fork	*lst;

	lst = malloc(sizeof(t_fork));
	if (!lst)
		return (NULL);
	pthread_mutex_init(&lst->num, NULL);
	lst->index = content;
	lst->number = 1;
	lst->global = global;
	lst->next = NULL;
	return (lst);
}

t_fork	*ft_lstlast_fork(t_fork *lst)
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

void	ft_lstadd_back_fork(t_fork **lst, t_fork *new)
{
	if (*lst)
		ft_lstlast_fork(*lst)->next = new;
	else
		*lst = new;
}
