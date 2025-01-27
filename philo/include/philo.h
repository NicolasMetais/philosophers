/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 03:19:22 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/27 05:05:57 by nmetais          ###   ########.fr       */
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

typedef enum s_boolean
{
	false,
	true,
}	t_boolean;

typedef struct s_fork
{
	pthread_mutex_t	num;
	int				number;
	int				index;
	t_global		*global;
	struct s_fork	*next;
}	t_fork;

typedef struct s_philo
{
	int					index;
	struct s_global		*global;
	t_fork				*fork_right;
	t_fork				*fork_left;
	t_boolean			eat;
	t_boolean			think;
	struct s_philo		*next;
}	t_philo;

typedef struct s_global
{
	long long		philo_num;
	long long		eat_timer;
	long long		die_timer;
	pthread_mutex_t	death;
	long			*death_check;
	long long		sleep_timer;
	pthread_mutex_t	timer;
	long			elapsed;
	pthread_mutex_t	exit;
	t_boolean		kill;
	t_philo			*philo;
	t_fork			*fork;
}		t_global;

long long	ft_atol(const char *nptr);
t_boolean	parse_args(char **av);
t_boolean	boring_life_setup(t_global *global);
int			linked_setup(t_global *global);

t_boolean	deathbringer(t_global *global);
void		burger_king(t_philo *philo);
void		mimimimi(t_philo *philo);
void		think(t_philo *philo);
t_boolean	isdead(t_global *global);

t_philo		*ft_lstlast_philo(t_philo *lst);
t_fork		*ft_lstlast_fork(t_fork *lst);
void		ft_lstadd_back_philo(t_philo **lst, t_philo *new);
void		ft_lstadd_back_fork(t_fork **lst, t_fork *new);
t_philo		*ft_lstnew_philo(int content, t_global *global, t_fork *fork);
t_fork		*ft_lstnew_fork(int content, t_global *global);

void		free_all(t_global *global);
void		emergency_free_fork(t_global *global);
void		emergency_free_philo(t_global *global);
#endif