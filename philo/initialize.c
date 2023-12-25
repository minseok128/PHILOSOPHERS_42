/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 19:47:01 by michang           #+#    #+#             */
/*   Updated: 2023/11/25 19:47:02 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_info(int argc, char **argv, t_info *info)
{
	memset(info, 0, sizeof(t_info));
	info->n_of_philo = ft_atol(argv[1]);
	info->t_to_die = ft_atol(argv[2]);
	info->t_to_eat = ft_atol(argv[3]);
	info->t_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		info->is_max_eat_mode = 1;
		info->max_eat = ft_atol(argv[5]);
	}
	if (info->n_of_philo <= 0 || info->t_to_die < 0 || info->t_to_eat < 0
		|| info->t_to_sleep < 0 || (info->is_max_eat_mode && info->max_eat < 0))
		return (1);
	if (pthread_mutex_init(&(info->ready_mutex), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(info->rsc_mutex), NULL) != 0)
	{
		pthread_mutex_destroy(&(info->ready_mutex));
		return (1);
	}
	return (0);
}

int	init_philo_arr(t_philo **arr, t_info *info)
{
	pthread_mutex_t	*fork_arr;
	int				i;

	*arr = malloc(sizeof(t_philo) * info->n_of_philo);
	if (!*arr)
		return (1);
	fork_arr = malloc(sizeof(pthread_mutex_t) * info->n_of_philo);
	if (!fork_arr)
		return (1);
	i = 0;
	while (i < info->n_of_philo)
	{
		pthread_mutex_init(&fork_arr[i], NULL);
		memset(&(*arr)[i], 0, sizeof(t_philo));
		(*arr)[i].info = info;
		(*arr)[i].id = i + 1;
		(*arr)[i].left_fork = &fork_arr[i];
		(*arr)[i].right_fork = &fork_arr[(i + 1) % info->n_of_philo];
		i++;
	}
	return (0);
}

int	start_philo(t_philo *arr, t_info *info)
{
	int	i;

	pthread_mutex_lock(&(info->ready_mutex));
	i = 0;
	while (i < info->n_of_philo)
	{
		if (pthread_create(&(arr[i].thread_id),
				NULL, (void *)p_action, &arr[i]) != 0)
		{
			info->is_error = 1;
			join_philos(arr, i - 1);
			pthread_mutex_unlock(&(info->ready_mutex));
			return (1);
		}
		printf("id:%d, thread_id:%d, left:%p, right:%p\n", arr[i].id, (int)arr[i].thread_id, arr[i].left_fork, arr[i].right_fork);
		i++;
	}
	info->t_to_start = get_time();
	pthread_mutex_unlock(&(info->ready_mutex));
	return (0);
}
