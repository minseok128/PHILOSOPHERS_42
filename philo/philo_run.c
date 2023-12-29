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

static int	p_single_mode(t_philo *p)
{
	if (p->info->n_of_philo != 1)
		return (0);
	pthread_mutex_lock(&(p->info->rsc_mutex));
	p_print(p, "is thinking\n");
	pthread_mutex_unlock(&(p->info->rsc_mutex));
	p_take_fork(p, 0);
	usleep(p->info->t_to_die * 1000);
	p_release_fork(p, 0);
	return (1);
}

static void	p_routine(t_philo *p)
{
	pthread_mutex_lock(&(p->info->rsc_mutex));
	while (p->info->program_state == RUN)
	{
		pthread_mutex_unlock(&(p->info->rsc_mutex));
		p_take_fork(p, p->id % 2);
		p_take_fork(p, !(p->id % 2));
		p_eat(p);
		p_release_fork(p, p->id % 2);
		p_release_fork(p, !(p->id % 2));
		if (p->n_of_eat == p->info->n_of_max_eat)
		{
			pthread_mutex_lock(&(p->info->rsc_mutex));
			p_print(p, "is sleeping\n");
			p->state = P_DONE;
			p->info->n_of_end_philo++;
			pthread_mutex_unlock(&(p->info->rsc_mutex));
			return ;
		}
		p_sleep(p);
		pthread_mutex_lock(&(p->info->rsc_mutex));
	}
	pthread_mutex_unlock(&(p->info->rsc_mutex));
}

void	*p_run(t_philo *p)
{
	long long	time;

	pthread_mutex_lock(&(p->info->ready_mutex));
	pthread_mutex_lock(&(p->info->rsc_mutex));
	p->t_to_last_eat = p->info->t_to_start;
	p->state = P_RUN;
	pthread_mutex_unlock(&(p->info->rsc_mutex));
	pthread_mutex_unlock(&(p->info->ready_mutex));
	if (p_single_mode(p))
		return (0);
	if (p->id % 2 == 0 || (p->id % 2 && p->id == p->info->n_of_philo))
	{
		pthread_mutex_lock(&(p->info->rsc_mutex));
		time = p_print(p, "is thinking\n");
		pthread_mutex_unlock(&(p->info->rsc_mutex));
		p_stop(p->info, time + p->info->t_to_eat / 2, time);
	}
	p_routine(p);
	return (0);
}
