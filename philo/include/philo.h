/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 03:19:22 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/25 05:29:28 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_global	t_global;

typedef struct s_philo
{
	int					index;
	struct s_global		*global;
	struct s_philo		*next;
}	t_philo;

typedef struct s_global
{
	long long		philo_num;
	long long		eat_timer;
	long long		die_timer;
	long long		sleep_timer;
	pthread_mutex_t	timer;
	long			elapsed;
	t_philo			*philo;
}		t_global;



typedef enum s_boolean
{
	false,
	true,
}	t_boolean;

long long	ft_atol(const char *nptr);
t_boolean	parse_args(char **av);
t_boolean	boring_life_setup(t_global *global);

t_philo		*ft_lstnew(int content, t_global *global);
t_philo		*ft_lstlast(t_philo *lst);
void		ft_lstadd_back(t_philo **lst, t_philo *new);
#endif