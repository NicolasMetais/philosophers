/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:57:55 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/27 00:12:32 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_boolean	deathbringer(t_global *global)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&global->death);
	while (++i < global->philo_num)
	{
		if (global->elapsed - global->death_check[i] >= global->die_timer)
		{
			pthread_mutex_unlock(&global->death);
			pthread_mutex_lock(&global->exit);
			global->kill = true;
			pthread_mutex_unlock(&global->exit);
			printf("%ld %d died\n", global->elapsed, (i + 1));
			return (false);
		}
	}
	pthread_mutex_unlock(&global->death);
	return (true);
}

void	fork_taker(t_philo *philo)
{
	philo->think = false;
	printf("%ld %d has taken a fork\n",
		philo->global->elapsed, philo->index);
	philo->fork_right->number = 0;
	printf("%ld %d has taken a fork\n",
		philo->global->elapsed, philo->index);
	philo->fork_left->number = 0;
}

void	burger_king(t_philo *philo)
{
	pthread_mutex_lock(&philo->global->exit);
	if (!philo->global->kill)
	{
		pthread_mutex_unlock(&philo->global->exit);
		fork_taker(philo);
		pthread_mutex_lock(&philo->global->timer);
		pthread_mutex_lock(&philo->global->death);
		philo->global->death_check[philo->index - 1] = philo->global->elapsed;
		pthread_mutex_unlock(&philo->global->death);
		pthread_mutex_unlock(&philo->global->timer);
		printf("%ld %d is eating\n", philo->global->elapsed, philo->index);
		usleep(philo->global->eat_timer * 1000);
		philo->fork_left->number = 1;
		philo->fork_right->number = 1;
		philo->eat = true;
	}
	pthread_mutex_unlock(&philo->global->exit);
}

void	mimimimi(t_philo *philo)
{
	if (!philo->global->kill)
	{
		philo->think = false;
		pthread_mutex_lock(&philo->global->timer);
		printf("%ld %d is sleeping\n", philo->global->elapsed, philo->index);
		pthread_mutex_unlock(&philo->global->timer);
		usleep(philo->global->sleep_timer * 1000);
		philo->eat = false;
	}
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->global->exit);
	if (!philo->think && !philo->global->kill)
	{
		pthread_mutex_unlock(&philo->global->exit);
		philo->think = true;
		pthread_mutex_lock(&philo->global->timer);
		printf("%ld %d is thinking\n", philo->global->elapsed, philo->index);
		pthread_mutex_unlock(&philo->global->timer);
	}
	pthread_mutex_unlock(&philo->global->exit);
}
