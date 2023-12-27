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

long long	get_time(void)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000L + (long long)tv.tv_usec / 1000L);
}

long long	p_print(t_philo *p, char *str)
{
	long long	time;

	if (p->info->is_error || p->info->is_dead)
		return (-1);
	time = get_time();
	printf("%lld %d %s", time - p->info->t_to_start, p->id, str);
	return (time);
}

void	join_philos(t_philo *arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
		pthread_join(arr[i++].thread_id, NULL);
}

int	print_error()
{
	printf("error\n");
	return (1);
}
