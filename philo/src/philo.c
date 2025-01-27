/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 06:17:43 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/27 17:19:47 by nmetais          ###   ########.fr       */
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
		pthread_mutex_unlock(&global->timer);
		if (!deathbringer(global) || !diet(global))
			return (NULL);
	}
	return (NULL);
}

/* void	fork_lock(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_right->num);
		pthread_mutex_lock(&philo->fork_left->num);
	}
	else
	{
		pthread_mutex_lock(&philo->fork_left->num);
		pthread_mutex_lock(&philo->fork_right->num);
	}
} */

t_boolean	isdead(t_global *global)
{
	t_boolean	alive;

	pthread_mutex_lock(&global->exit);
	alive = global->kill;
	pthread_mutex_unlock(&global->exit);
	return (alive);
}

t_boolean	philo_desynch(t_philo *philo)
{
	if (philo->index % 2 != 0 || philo->global->philo_num == 1)
	{
		if (!think(philo))
			return (false);
		if (usleep(500) == -1)
			return (false);
	}
	return (true);
}

void	*philo_exec(void *data)
{
	t_philo		*philo;
	int			index;

	philo = data;
	index = philo->index;
	philo->diet = 0;
	if (!philo_desynch(philo))
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&philo->fork_left->num);
		pthread_mutex_lock(&philo->fork_right->num);
		if (philo->fork_left->number && philo->fork_right->number)
			burger_king(philo);
		pthread_mutex_unlock(&philo->fork_left->num);
		pthread_mutex_unlock(&philo->fork_right->num);
		if (philo->eat)
			mimimimi(philo);
		think(philo);
		if (isdead(philo->global))
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
	return (true);
}
