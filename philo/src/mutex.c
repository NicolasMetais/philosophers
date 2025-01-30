/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:42:38 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/31 00:22:50 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_actions(t_global *global, int index, char *toprint)
{
	pthread_mutex_lock(&global->timer);
	printf("%ld %d %s\n", global->elapsed, index, toprint);
	pthread_mutex_unlock(&global->timer);
}

void	set_time(t_global *global, struct timeval start,
	struct timeval current)
{
	pthread_mutex_lock(&global->timer);
	global->elapsed = (current.tv_sec - start.tv_sec) * 1000
		+ (current.tv_usec - start.tv_usec) / 1000;
	pthread_mutex_unlock(&global->timer);
}

t_boolean	death_checker(t_global *global, int i)
{
	t_boolean	death;

	pthread_mutex_lock(&global->timer);
	pthread_mutex_lock(&global->death);
	if (global->elapsed - global->death_check[i] >= global->die_timer)
		death = true;
	else
		death = false;
	pthread_mutex_unlock(&global->timer);
	pthread_mutex_unlock(&global->death);
	return (death);
}

void	reset_life_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->global->timer);
	pthread_mutex_lock(&philo->global->death);
	philo->global->death_check[philo->index - 1] = philo->global->elapsed;
	pthread_mutex_unlock(&philo->global->timer);
	pthread_mutex_unlock(&philo->global->death);
}
