/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 06:17:43 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/26 05:28:10 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*timer(void *data)
{
	struct timeval	start;
	struct timeval	current;
	t_global		*global;

	global = data;
	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&current, NULL);
 		pthread_mutex_lock(&global->timer);
		global->elapsed = (current.tv_sec - start.tv_sec) * 1000
			+ (current.tv_usec - start.tv_usec) / 1000;
		if (!deathbringer(global))
		{
			pthread_mutex_unlock(&global->timer);
			return (NULL);
		}
		pthread_mutex_unlock(&global->timer);
	}
	return (NULL);
}

void	*philo_exec(void *data)
{
	t_philo		*philo;
	int			index;
	int			fork;
	t_boolean	trigger;

	philo = data;
	philo->eat = false;
	trigger = true;
	index = philo->index;
	fork = 1;
	while (1)
	{
		pthread_mutex_lock(&philo->fork_left->num);
		pthread_mutex_lock(&philo->fork_right->num);
		if (trigger && index % 2 != 0)
		{
			burger_king(philo);
		}
		else
			think(philo);
		if (philo->fork_left->number == 1
			&& philo->fork_right->number == 1 && !trigger)
			burger_king(philo);
		else
		{
			think(philo);
		}
		if (philo->eat)
			mimimimi(philo);
		if (trigger)
			trigger = false;
		if (philo->global->kill == true)
			return (NULL);
	}
}

t_boolean	boring_life_setup(t_global *global)
{
	pthread_t	*thread;
	t_philo		*temp;
	int			i;

	temp = global->philo;
	thread = malloc(sizeof(pthread_t) * (global->philo_num + 1));
	if (!thread)
		return (false);
	pthread_create(&thread[0], NULL, timer, global);
	i = 0;
	while (++i < global->philo_num + 1)
	{
		pthread_create(&thread[i], NULL, philo_exec, temp);
		temp = temp->next;
	}
	i = (int)global->philo_num + 1;
	while (i > 0)
		pthread_join(thread[--i], NULL);
	free(thread);
	free(global->death_check);
	return (true);
}
