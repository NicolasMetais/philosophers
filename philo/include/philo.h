/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 03:19:22 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/21 22:11:19 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_philo
{
	long long		philo_num;
	long long		eat_timer;
	long long		die_timer;
	long long		sleep_timer;
}		t_philo;

typedef enum s_boolean
{
	false,
	true,
}	t_boolean;

long long	ft_atol(const char *nptr);
t_boolean	parse_args(char **av);
t_boolean	boring_life_setup(t_philo *philo);

#endif