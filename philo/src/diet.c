/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diet.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:42:47 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/31 00:21:56 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_boolean	die_condition(t_global *global)
{
	pthread_mutex_lock(&global->exit);
	global->kill = true;
	pthread_mutex_unlock(&global->exit);
	return (false);
}

t_boolean	diet(t_global *global)
{
	int			i;
	int			count;
	t_boolean	bol;

	bol = false;
	count = 0;
	if (global->diet)
	{
		i = -1;
		while (++i < global->philo_num)
		{
			pthread_mutex_lock(&global->count);
			if (global->eat_count[i] == global->max_diet)
			{
				bol = true;
				count++;
			}
			else
				bol = false;
			pthread_mutex_unlock(&global->count);
		}
		if (count == global->philo_num)
			return (die_condition(global));
	}
	return (true);
}
