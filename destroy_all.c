/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 06:12:47 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/07 06:17:45 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void destroy_mutex(pthread_mutex_t *forks, t_program *program)
{
    int i = 0;
    while (i < program->num_philo)
        pthread_mutex_destroy(&forks[i++]);
}