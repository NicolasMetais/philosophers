/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:46:53 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/28 04:53:31 by nmetais          ###   ########.fr       */
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