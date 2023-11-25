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

void	init_info(char **argv, t_info *info)
{
	info->n_of_philos = ft_atol(argv[1]);
	info->t_to_die = ft_atol(argv[2]);
	info->t_to_sleep = ft_atol(argv[3]);
	info->n_of_t_must_eat = ft_atol(argv[4]);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (!(argc == 4 || argc == 5))
		return (1);
	init_info(argv, &info);
	write(0, "hello philo!", 12);
	return (0);
}
