/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diet.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:42:47 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/27 17:24:14 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_boolean	diet(t_global *global)
{
	int			i;
	t_boolean	bol;

	bol = false;
	if (global->diet)
	{
		i = -1;
		while (++i < global->philo_num)
		{
			pthread_mutex_lock(&global->count);
			if (global->eat_count[i] == global->max_diet)
				bol = true;
			else
				bol = false;
			pthread_mutex_unlock(&global->count);
		}
		if (bol == true)
		{
			pthread_mutex_lock(&global->exit);
			global->kill = true;
			pthread_mutex_unlock(&global->exit);
			return (false);
		}
	}
	return (true);
}
