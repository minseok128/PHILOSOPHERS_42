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
	long long		n_of_max_eat;
	long long		t_to_must_think;
	int				is_dead;
	int				is_error;
	int				n_of_end_philo;
	pthread_mutex_t	ready_mutex;
	pthread_mutex_t	rsc_mutex;
	pthread_mutex_t	*fork_arr;
}	t_info;

typedef struct s_philo
{
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_info			*info;
	int				id;
	int				n_of_eat;
	int				is_done;
	long long		t_to_last_eat;
}	t_philo;

# define	P_LIVE 0;
# define	P_DONE 1;
# define	P_DEAD 2;

# define	FALSE 0;
# define	TRUE 1;

long long	get_time();
int			print_error();
long long	ft_atol(const char *str);
int			init_info(int argc, char **argv, t_info *info);
int			init_philos(t_philo **arr, t_info *info);
int			start_philos(t_philo *arr, t_info *info);
void		join_philos(t_philo *arr, int n);
long long	p_print(t_philo *p, char *str);
void		*p_action(t_philo *p);
int			start_monitor(t_philo *philos, t_info *info);

#endif