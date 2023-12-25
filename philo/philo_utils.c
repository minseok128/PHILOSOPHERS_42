/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 17:12:43 by michang           #+#    #+#             */
/*   Updated: 2023/12/22 17:12:45 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_timer(t_info *info, long long limit, long long time, int sleep_time)
{
	limit += get_time();
	pthread_mutex_lock(&(info->rsc_mutex));
	while (!info->is_dead && limit > time)
	{
		pthread_mutex_unlock(&(info->rsc_mutex));
		usleep(sleep_time);
		time = get_time();
		pthread_mutex_lock(&(info->rsc_mutex));
	}
	pthread_mutex_unlock(&(info->rsc_mutex));
	return (1);
}

void	p_sleep(t_philo *p, int sleep_time)
{
	long long	limit_time;
	long long	time;

	pthread_mutex_lock(&(p->info->rsc_mutex));
	time = p_print(p, "is sleeping\n");
	if (time != -1)
	{
		limit_time = time + p->info->t_to_sleep;
		pthread_mutex_unlock(&(p->info->rsc_mutex));
		if (p_timer(p->info, limit_time, time, sleep_time) == -1)
			return ;
		pthread_mutex_lock(&(p->info->rsc_mutex));
		time = p_print(p, "is thinking\n");
		pthread_mutex_unlock(&(p->info->rsc_mutex));
	}
	else
		pthread_mutex_unlock(&(p->info->rsc_mutex));
}

void	p_eat(t_philo *p, int sleep_time)
{
	long long	limit;
	long long	time;

	pthread_mutex_lock(&(p->info->rsc_mutex));
	time = p_print(p, "is eating\n");
	if (time != -1)
	{
		p->t_to_last_eat = time;
		limit = time + p->info->t_to_eat;
		pthread_mutex_unlock(&(p->info->rsc_mutex));
		if (p_timer(p->info, limit, time, sleep_time) == -1)
			return ;
		p->n_of_eat += p->info->is_max_eat_mode;
	}
	else
		pthread_mutex_unlock(&(p->info->rsc_mutex));
}

void	p_take_fork(t_philo *p, int right)
{
	if (right)
	{
		pthread_mutex_lock(p->right_fork);
		pthread_mutex_lock(&(p->info->rsc_mutex));
		p_print(p, "has taken a fork\n");
		// printf("right: %p\n", p->right_fork);
		pthread_mutex_unlock(&(p->info->rsc_mutex));
	}
	else
	{
		pthread_mutex_lock(p->left_fork);
		pthread_mutex_lock(&(p->info->rsc_mutex));
		p_print(p, "has taken a fork\n");
		// printf("left: %p\n", p->left_fork);
		pthread_mutex_unlock(&(p->info->rsc_mutex));
	}
}

void	p_release_fork(t_philo *p, int right)
{
	// p_print(p, "has release a fork\n");
	if (right)
		pthread_mutex_unlock(p->right_fork);
	else
		pthread_mutex_unlock(p->left_fork);
}

void	p_action(t_philo *p)
{
	pthread_mutex_lock(&(p->info->ready_mutex));
    pthread_mutex_lock(&(p->info->rsc_mutex));
    p->is_start = 1;
    p->t_to_last_eat = p->info->t_to_start;
	pthread_mutex_unlock(&(p->info->rsc_mutex));
	pthread_mutex_unlock(&(p->info->ready_mutex));
	if (p->info->is_error)
		return ;
	while (1)
	{
		pthread_mutex_lock(&(p->info->rsc_mutex));
		while (!p->info->is_dead && !p->info->is_error)
		{
			pthread_mutex_unlock(&(p->info->rsc_mutex));
			p_take_fork(p, p->id % 2);
			p_take_fork(p, !(p->id % 2));
			p_eat(p, p->info->n_of_philo);
			p_release_fork(p, !(p->id % 2));
			p_release_fork(p, p->id % 2);
			p_sleep(p, p->info->n_of_philo);
		}
	}
}

void	join_philos(t_philo *arr, int n)
{
	int	i;

	i = 0;
	while (i <= n)
		pthread_join(arr[i++].thread_id, NULL);
}
