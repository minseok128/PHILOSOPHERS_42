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

void	p_stop(t_info *info, long long target_time, long long time)
{
	pthread_mutex_lock(&(info->rsc_mutex));
	while (!info->is_dead && target_time > time)
	{
		pthread_mutex_unlock(&(info->rsc_mutex));
		usleep(info->n_of_philo);
		time = get_time();
		pthread_mutex_lock(&(info->rsc_mutex));
	}
	pthread_mutex_unlock(&(info->rsc_mutex));
}

void	p_sleep(t_philo *p)
{
	long long	time;

	pthread_mutex_lock(&(p->info->rsc_mutex));
	time = p_print(p, "is sleeping\n");
	if (time != -1)
	{
		pthread_mutex_unlock(&(p->info->rsc_mutex));
		p_stop(p->info, time + p->info->t_to_sleep, time);
		pthread_mutex_lock(&(p->info->rsc_mutex));
		time = p_print(p, "is thinking\n");
		pthread_mutex_unlock(&(p->info->rsc_mutex));
	}
	else
		pthread_mutex_unlock(&(p->info->rsc_mutex));
}

void	p_eat(t_philo *p)
{
	long long	time;

	pthread_mutex_lock(&(p->info->rsc_mutex));
	time = p_print(p, "is eating\n");
	if (time != -1)
	{
		p->t_to_last_eat = time;
		pthread_mutex_unlock(&(p->info->rsc_mutex));
		p_stop(p->info, time + p->info->t_to_eat, time);
		p->n_of_eat++;
	}
	else
		pthread_mutex_unlock(&(p->info->rsc_mutex));
}

void	p_take_fork(t_philo *p, int right)
{
	if (right)
		pthread_mutex_lock(p->right_fork);
	else
		pthread_mutex_lock(p->left_fork);
	pthread_mutex_lock(&(p->info->rsc_mutex));
	p_print(p, "has taken a fork\n");
	pthread_mutex_unlock(&(p->info->rsc_mutex));
}

void	p_release_fork(t_philo *p, int right)
{
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
			p_eat(p);
			p_release_fork(p, p->id % 2);
			p_release_fork(p, !(p->id % 2));
			p_sleep(p);
			pthread_mutex_lock(&(p->info->rsc_mutex));
		}
		pthread_mutex_unlock(&(p->info->rsc_mutex));
	}
}
