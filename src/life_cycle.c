/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:57:55 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/31 00:22:25 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_boolean	deathbringer(t_global *global)
{
	int	i;

	i = -1;
	while (++i < global->philo_num)
	{
		if (death_checker(global, i))
		{
			pthread_mutex_lock(&global->exit);
			global->kill = true;
			pthread_mutex_unlock(&global->exit);
			print_actions(global, i + 1, "died");
			return (false);
		}
	}
	return (true);
}

void	fork_taker(t_philo *philo)
{
	philo->think = false;
	print_actions(philo->global, philo->index, "has taken a fork");
	philo->fork_right->number = 0;
	print_actions(philo->global, philo->index, "has taken a fork");
	philo->fork_left->number = 0;
	unlock_fork(philo->global);
}

void	burger_king(t_philo *philo)
{
	if (!isdead(philo->global))
	{
		fork_taker(philo);
		reset_life_time(philo);
		print_actions(philo->global, philo->index, "is eating");
		if (usleep(philo->global->eat_timer * 1000) == -1)
			return ;
		lock_fork(philo->global);
		philo->fork_left->number = 1;
		philo->fork_right->number = 1;
		unlock_fork(philo->global);
		philo->eat = true;
		if (philo->global->diet)
		{
			pthread_mutex_lock(&philo->global->count);
			philo->global->eat_count[philo->index - 1] += 1;
			pthread_mutex_unlock(&philo->global->count);
		}
	}
	else
		unlock_fork(philo->global);
}

void	mimimimi(t_philo *philo)
{
	if (!isdead(philo->global))
	{
		philo->think = false;
		print_actions(philo->global, philo->index, "is sleeping");
		philo->eat = false;
		usleep(philo->global->sleep_timer * 1000);
	}
}

t_boolean	think(t_philo *philo)
{
	if (philo->global->philo_num == 1)
	{
		print_actions(philo->global, philo->index, "is thinking");
		if (usleep(philo->global->die_timer) == -1)
			return (false);
		return (false);
	}
	if (!isdead(philo->global))
	{
		if (philo->think == false)
		{
			philo->think = true;
			print_actions(philo->global, philo->index, "is thinking");
			usleep(1000);
		}
	}
	return (true);
}
