/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:45:12 by michang           #+#    #+#             */
/*   Updated: 2023/12/26 19:45:13 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_check(t_info *info, t_philo *p)
{
	long long	time;

	time = get_time();
	if (p->t_to_last_eat && time - p->t_to_last_eat >= info->t_to_die)
	{
		info->is_dead = 1;
		printf("%lld %d died\n", time - info->t_to_start, p->id);
	}
}

void	start_monitor(t_philo *philos, t_info *info)
{
	int i;

	while (1)
	{
		i = 0;
		while (i < info->n_of_philo)
		{
			pthread_mutex_lock(&(info->rsc_mutex));
			p_check(info, &(philos[i]));
			if (info->is_dead || info->is_error)
			{
				pthread_mutex_unlock(&(info->rsc_mutex));
				return ;
			}
			i++;
			pthread_mutex_unlock(&(info->rsc_mutex));
		}
	}
}
