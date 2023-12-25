/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:15:57 by michang           #+#    #+#             */
/*   Updated: 2023/12/22 18:15:58 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time()
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	// printf("get_time: %lld, %lld\n", (long long)tv.tv_sec, (long long)tv.tv_usec);
	return ((long long)tv.tv_sec * 1000L + (long long)tv.tv_usec / 1000L);
}

long long	p_print(t_philo *p, char *str)
{
	long long	time;

	if (p->info->is_error || p->info->is_dead)
		return (-1);
	time = get_time() - p->info->t_to_start;
	printf("%lld %d %s", time, p->id, str);
	return (time);
}
