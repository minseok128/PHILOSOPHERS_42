/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:55:14 by michang           #+#    #+#             */
/*   Updated: 2023/12/29 16:55:15 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_stop(t_info *info, long long target_time, long long time)
{
	pthread_mutex_lock(&(info->rsc_mutex));
	while (info->program_state == RUN && target_time > time)
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
		if (p->info->t_to_must_think >= 0 && p->info->n_of_philo % 2)
		{
			p_stop(p->info, time + p->info->t_to_must_think, time);
			usleep(200);
		}
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
