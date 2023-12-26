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

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*arr;

	if (!(argc == 5 || argc == 6))
		return (1);
	if (init_info(argc, argv, &info))
		return (1);
	if (init_philos(&arr, &info))
		return (1);
	start_philos(arr, &info);
	join_philos(arr, info.n_of_philo);
	return (0);
}
