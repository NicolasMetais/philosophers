/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 06:17:43 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/25 05:44:09 by nmetais          ###   ########.fr       */
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
		printf("\nELAPSED %ld\n", global->elapsed);
		pthread_mutex_unlock(&global->timer);
		usleep(1000);
	}
	return (NULL);
}

void	*philo_exec(void *data)
{
	t_philo		*philo;
	int			index;
	int			fork;
	t_boolean	eat;

	philo = data;
	index = philo->index;
	printf("INDEX %d\n", index);
	fork = 1;
	eat = false;
	pthread_mutex_lock(&philo->global->timer);
	printf("%ld\n", philo->global->elapsed);
	pthread_mutex_unlock(&philo->global->timer);
	return (NULL);
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
	pthread_mutex_init(&global->timer, NULL);
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
	pthread_mutex_destroy(&global->timer);
	free(thread);
	return (true);
}
