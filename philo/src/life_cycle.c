/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:57:55 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/28 04:59:27 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_boolean	deathbringer(t_global *global)
{
	int	i;

	i = -1;
	while (++i < global->philo_num)
	{
		pthread_mutex_lock(&global->timer);
		pthread_mutex_lock(&global->death);
		if (global->elapsed - global->death_check[i] >= global->die_timer)
		{
			pthread_mutex_unlock(&global->timer);
			pthread_mutex_unlock(&global->death);
			pthread_mutex_lock(&global->exit);
			global->kill = true;
			pthread_mutex_unlock(&global->exit);
			pthread_mutex_lock(&global->timer);
			printf("%ld %d died\n", global->elapsed, (i + 1));
			pthread_mutex_unlock(&global->timer);
			return (false);
		}
		else
		{
			pthread_mutex_unlock(&global->timer);
			pthread_mutex_unlock(&global->death);
		}
	}
	return (true);
}

void	fork_taker(t_philo *philo)
{
	philo->think = false;
	pthread_mutex_lock(&philo->global->timer);
	printf("%ld %d has taken a fork\n",
		philo->global->elapsed, philo->index);
	philo->fork_right->number = 0;
	printf("%ld %d has taken a fork\n",
		philo->global->elapsed, philo->index);
	pthread_mutex_unlock(&philo->global->timer);
	philo->fork_left->number = 0;
	unlock_fork(philo->global);
}

void	burger_king(t_philo *philo)
{
	if (!isdead(philo->global))
	{
		fork_taker(philo);
		unlock_fork(philo->global);
		pthread_mutex_lock(&philo->global->timer);
		pthread_mutex_lock(&philo->global->death);
		philo->global->death_check[philo->index - 1] = philo->global->elapsed;
		pthread_mutex_unlock(&philo->global->death);
		pthread_mutex_unlock(&philo->global->timer);
		pthread_mutex_lock(&philo->global->timer);
		printf("%ld %d is eating\n", philo->global->elapsed, philo->index);
		pthread_mutex_unlock(&philo->global->timer);
		usleep(philo->global->eat_timer * 1000);
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
		pthread_mutex_lock(&philo->global->timer);
		printf("%ld %d is sleeping\n", philo->global->elapsed, philo->index);
		pthread_mutex_unlock(&philo->global->timer);
		usleep(philo->global->sleep_timer * 1000);
		philo->eat = false;
	}
}

t_boolean	think(t_philo *philo)
{
	if (philo->global->philo_num == 1)
	{
		pthread_mutex_lock(&philo->global->timer);
		printf("%ld %d is thinking\n", philo->global->elapsed, philo->index);
		pthread_mutex_unlock(&philo->global->timer);
		if (usleep(philo->global->die_timer) == -1)
			return (false);
		return (false);
	}
	if (!isdead(philo->global) && philo->think == false)
	{
		philo->think = true;
		pthread_mutex_lock(&philo->global->timer);
		printf("%ld %d is thinking\n", philo->global->elapsed, philo->index);
		pthread_mutex_unlock(&philo->global->timer);
/*  		if (usleep((philo->global->eat_timer - 2) * 1000) == -1)
			return (false); */
	}
	return (true);
}
