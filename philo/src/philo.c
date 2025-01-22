/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 06:17:43 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/22 02:47:41 by nmetais          ###   ########.fr       */
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

t_boolean	boring_life_setup(t_philo *philo)
{
	pthread_t	timer_ms;

	(void)philo;
	printf("SUCCES");
	pthread_create(&timer_ms, NULL, timer, NULL);
	pthread_join(timer_ms, NULL);
	return (true);
}
