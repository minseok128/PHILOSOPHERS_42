/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:18:56 by michang           #+#    #+#             */
/*   Updated: 2023/11/25 16:18:59 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_info(int argc, char **argv, t_info *info)
{
	info->n_of_philo = ft_atol(argv[1]);
	info->t_to_die = ft_atol(argv[2]);
	info->t_to_eat = ft_atol(argv[3]);
	info->t_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		info->max_eat_mode = 1;
		info->max_eat = ft_atol(argv[5]);
	}
	else
		info->max_eat_mode = 0;
	if (info->n_of_philo <= 0 || info->t_to_die <= 0 || info->t_to_eat <= 0
		|| info->t_to_sleep <= 0 || (info->max_eat_mode && info->max_eat <= 0))
		return (1);
	info->dead = 0;
	info->error = 0;
	info->end_philo = 0;
	return (0);
	// printf("%lld, %lld, %lld, %lld\n", info->n_of_philo, info->t_to_die, info->t_to_sleep, info->max_eat);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (!(argc == 5 || argc == 6))
		return (1);
	if (init_info(argc, argv, &info))
		return (1);
	write(0, "hello philo!", 12);
	return (0);
}
