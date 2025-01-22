/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 06:17:43 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/22 05:00:32 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*timer(void *data)
{
	struct timeval	start;
	struct timeval	current;
	long			elapsed;

	(void) data;
	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&current, NULL);
		elapsed = (current.tv_sec - start.tv_sec) * 1000
			+ (current.tv_usec - start.tv_usec) / 1000;
	}
	return (NULL);
}

void	*philo_exec(void *data)
{
	t_global	*global;
	int			index;

	global = data;
	printf("%d\n", index);
	return (NULL);
}

t_boolean	boring_life_setup(t_global *global)
{
	pthread_t	thread;
	int			i;

	i = 0;
	printf("SUCCES\n");
	pthread_create(&thread, NULL, timer, NULL);
	while (i < (int)global->philo_num)
	{
		pthread_create(&thread, NULL, philo_exec, global);
		sleep(1);
		i++;
	}
	while (i < (int)global->philo_num + 1)
	{
		pthread_join(thread, NULL);
		i++;
	}
	return (true);
}
