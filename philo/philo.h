/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:20:19 by michang           #+#    #+#             */
/*   Updated: 2023/11/25 16:20:20 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct s_info {
	long long		n_of_philo;
	long long		t_to_start;
	long long		t_to_die;
	long long		t_to_eat;
	long long		t_to_sleep;
	long long		max_eat;
	int				is_max_eat_mode;
	int				is_dead;
	int				is_error;
	int				n_of_end_philo;
	pthread_mutex_t	ready_mutex;
	pthread_mutex_t	rsc_mutex;
}	t_info;

typedef struct s_philo
{
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_info			*info;
	int				id;
	int				is_start;
	int				n_of_eat;
	long long		t_to_last_eat;
}	t_philo;

long long	get_time();
long long	ft_atol(const char *str);
int			init_info(int argc, char **argv, t_info *info);
int			init_philos(t_philo **arr, t_info *info);
int			start_philos(t_philo *arr, t_info *info);
void		join_philos(t_philo *arr, int n);
long long	p_print(t_philo *p, char *str);
void		p_action(t_philo *p);

#endif