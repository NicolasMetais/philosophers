/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:46:53 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/30 20:53:52 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	lock_fork(t_global *global)
{
	pthread_mutex_lock(&global->philo->fork_left->num);
	pthread_mutex_lock(&global->philo->fork_right->num);
}

void	unlock_fork(t_global *global)
{
	pthread_mutex_unlock(&global->philo->fork_left->num);
	pthread_mutex_unlock(&global->philo->fork_right->num);
}

t_boolean	fork_checker(t_philo *philo)
{
	lock_fork(philo->global);
	if (philo->fork_left->number && philo->fork_right->number)
		return (true);
	else
		return (unlock_fork(philo->global), false);
}
