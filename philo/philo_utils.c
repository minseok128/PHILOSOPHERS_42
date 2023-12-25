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

void	take_fork(t_philo *p, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	pthread_mutex_unlock(fork);
}

void	action_philo(t_philo *p)
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
		printf("%d, here!\n", p->id);
		pthread_mutex_unlock(&(p->info->rsc_mutex));
		usleep(500000);
	}
}

void	join_philos(t_philo *arr, int n)
{
	int	i;

	i = 0;
	while (i <= n)
		pthread_join(arr[i++].thread_id, NULL);
}
