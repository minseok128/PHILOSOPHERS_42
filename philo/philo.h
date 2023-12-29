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

typedef enum e_program_state {
	READY = 0,
	RUN,
	DONE,
	ERROR
}	t_program_state;

typedef struct s_info {
	long long		n_of_philo;
	long long		t_to_start;
	long long		t_to_die;
	long long		t_to_eat;
	long long		t_to_sleep;
	long long		t_to_must_think;
	long long		n_of_max_eat;
	int				n_of_end_philo;
	t_program_state	program_state;
	pthread_mutex_t	ready_mutex;
	pthread_mutex_t	rsc_mutex;
	pthread_mutex_t	*fork_arr;
}	t_info;

typedef enum e_philo_state {
	P_READY = 0,
	P_RUN,
	P_DONE,
	P_DEAD
}	t_philo_state;

typedef struct s_philo
{
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_info			*info;
	t_philo_state	state;
	int				id;
	int				n_of_eat;
	long long		t_to_last_eat;
}	t_philo;

// program functions
int			init_info(int argc, char **argv, t_info *info);
int			init_philos(t_philo **arr, t_info *info);
int			start_philos(t_philo *arr, t_info *info);
void		start_monitor(t_philo *philos, t_info *info);
void		join_philos(t_philo *arr, int n);
int			clean_all(t_philo *philos, t_info *info, int n);

// each philo functions
void		*p_run(t_philo *p);
long long	p_print(t_philo *p, char *str);
void		p_eat(t_philo *p);
void		p_take_fork(t_philo *p, int right);
void		p_release_fork(t_philo *p, int right);
void		p_sleep(t_philo *p);
void		p_stop(t_info *info, long long target_time, long long time);

// util functions
long long	get_time(void);
long long	ft_atoll(const char *str);

#endif