/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:36:31 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/25 05:28:58 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_lstnew(int content, t_global *global)
{
	t_philo	*lst;

	lst = malloc(sizeof(t_philo));
	if (!lst)
		return (NULL);
	lst->index = content;
	lst->global = global;
	lst->next = NULL;
	return (lst);
}

t_philo	*ft_lstlast(t_philo *lst)
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

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}
