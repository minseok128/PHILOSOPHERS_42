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
	if (argc < 5 || argc > 6)
		return (1);
	memset(info, 0, sizeof(t_info));
	info->n_of_philo = ft_atoll(argv[1]);
	info->t_to_die = ft_atoll(argv[2]);
	info->t_to_eat = ft_atoll(argv[3]);
	info->t_to_sleep = ft_atoll(argv[4]);
	if (argc == 6)
		info->n_of_max_eat = ft_atoll(argv[5]);
	if ((info->n_of_philo <= 0 || info->t_to_die < 0 || info->t_to_eat < 0
			|| info->t_to_sleep < 0 || (argc == 6 && info->n_of_max_eat <= 0))
		|| (pthread_mutex_init(&(info->ready_mutex), NULL) != 0))
		return (1);
	if (pthread_mutex_init(&(info->rsc_mutex), NULL) != 0)
	{
		pthread_mutex_destroy(&(info->ready_mutex));
		return (1);
	}
	info->t_to_must_think = info->t_to_eat - info->t_to_sleep;
	return (0);
}

int	init_philos(t_philo **philos, t_info *info)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * info->n_of_philo);
	info->fork_arr = malloc(sizeof(pthread_mutex_t) * info->n_of_philo);
	if (!(*philos) || !(info->fork_arr))
		return (clean_all(*philos, info, 0));
	memset(*philos, 0, sizeof(t_philo) * info->n_of_philo);
	i = 0;
	while (i < info->n_of_philo)
	{
		if (pthread_mutex_init(&(info->fork_arr[i]), NULL) != 0)
			return (clean_all(*philos, info, i));
		(*philos)[i].info = info;
		(*philos)[i].id = i + 1;
		(*philos)[i].left_fork = &(info->fork_arr[i]);
		(*philos)[i].right_fork = &(info->fork_arr[(i + 1) % info->n_of_philo]);
		i++;
	}
	return (0);
}

int	start_philos(t_philo *philos, t_info *info)
{
	int	i;

	pthread_mutex_lock(&(info->ready_mutex));
	i = 0;
	while (i < info->n_of_philo)
	{
		if (pthread_create(&(philos[i].thread_id),
				NULL, (void *)p_run, &philos[i]) != 0)
		{
			info->program_state = ERROR;
			pthread_mutex_unlock(&(info->ready_mutex));
			join_philos(philos, i);
			return (clean_all(philos, info, info->n_of_philo));
		}
		i++;
	}
	info->program_state = RUN;
	info->t_to_start = get_time();
	pthread_mutex_unlock(&(info->ready_mutex));
	return (0);
}

void	join_philos(t_philo *arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
		pthread_join(arr[i++].thread_id, NULL);
}
