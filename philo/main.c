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
	t_philo	*philos;

	if (init_info(argc, argv, &info)
		|| init_philos(&philos, &info)
		|| start_philos(philos, &info))
		return (printf("ERROR") & 1);
	start_monitor(philos, &info);
	join_philos(philos, info.n_of_philo);
	clean_all(philos, &info, info.n_of_end_philo);
	return (0);
}
