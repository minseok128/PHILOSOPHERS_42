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

long long	ft_atoll(const char *str)
{
	unsigned int	i;
	int				tmp;
	long long		result;
	int				sign;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = str[i] - '0';
		result = result * 10 + tmp;
		i++;
	}
	return (result * sign);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000L + (long long)tv.tv_usec / 1000L);
}

void	join_philos(t_philo *arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
		pthread_join(arr[i++].thread_id, NULL);
}

long long	p_print(t_philo *p, char *str)
{
	long long	time;

	if (p->info->program_state != RUN)
		return (-1);
	time = get_time();
	printf("%lld %d %s", time - p->info->t_to_start, p->id, str);
	return (time);
}

int	print_error(void)
{
	printf("error\n");
	return (1);
}
