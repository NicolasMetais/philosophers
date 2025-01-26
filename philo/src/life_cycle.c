/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:57:55 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/26 06:01:04 by nmetais          ###   ########.fr       */
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
			global->kill = true;
			printf("%ld %d died\n", global->elapsed, (i + 1));
			pthread_mutex_unlock(&global->death);
			return (false);
		}
	}
	pthread_mutex_unlock(&global->death);
	return (true);
}

void	burger_king(t_philo *philo)
{
	if (!philo->global->kill)
	{
		printf("%ld %d has taken a fork\n",
			philo->global->elapsed, philo->index);
		philo->fork_left->number = 0;
		printf("%ld %d has taken a fork\n",
			philo->global->elapsed, philo->index);
		philo->fork_right->number = 0;
		pthread_mutex_unlock(&philo->fork_left->num);
		pthread_mutex_unlock(&philo->fork_right->num);
		pthread_mutex_lock(&philo->global->timer);
		pthread_mutex_lock(&philo->global->death);
		philo->global->death_check[philo->index - 1] = philo->global->elapsed;
		pthread_mutex_unlock(&philo->global->death);
		printf("%ld %d is eating\n", philo->global->elapsed, philo->index);
		pthread_mutex_unlock(&philo->global->timer);
		usleep(philo->global->eat_timer * 1000);
		pthread_mutex_lock(&philo->fork_left->num);
		pthread_mutex_lock(&philo->fork_right->num);
		philo->fork_left->number = 1;
		philo->fork_right->number = 1;
		pthread_mutex_unlock(&philo->fork_left->num);
		pthread_mutex_unlock(&philo->fork_right->num);
		philo->eat = true;
	}
}

void	mimimimi(t_philo *philo)
{
	if (!philo->global->kill)
	{
		pthread_mutex_lock(&philo->global->timer);
		printf("%ld %d is sleeping\n", philo->global->elapsed, philo->index);
		pthread_mutex_unlock(&philo->global->timer);
		usleep(philo->global->sleep_timer * 1000);
		philo->eat = false;
	}
}

void	think(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork_left->num);
	pthread_mutex_unlock(&philo->fork_right->num);
	pthread_mutex_lock(&philo->global->timer);
	printf("%ld %d is thinking\n", philo->global->elapsed, philo->index);
	pthread_mutex_unlock(&philo->global->timer);
	while (1)
	{
		pthread_mutex_lock(&philo->fork_left->num);
		pthread_mutex_lock(&philo->fork_right->num);
		if (philo->global->kill || (philo->fork_left->number == 1
				&& philo->fork_right->number == 1))
		{
			pthread_mutex_unlock(&philo->fork_left->num);
			pthread_mutex_unlock(&philo->fork_right->num);
			break ;
		}
		pthread_mutex_unlock(&philo->fork_left->num);
		pthread_mutex_unlock(&philo->fork_right->num);
		usleep(100);
	}
}
