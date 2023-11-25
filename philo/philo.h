/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:20:19 by michang           #+#    #+#             */
/*   Updated: 2023/11/25 16:20:20 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_info {
    long long   n_of_philos;
    long long   t_to_die;
    long long   t_to_sleep;
    long long   n_of_t_must_eat;
} t_info;

long long	ft_atol(const char *str);

#endif