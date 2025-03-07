/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 05:57:36 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/07 06:08:27 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void init_mutex(pthread_mutex_t *forks, t_program *program)
{
    int i = 0;
    while (i < program->num_philo)
        pthread_mutex_init(&forks[i++], NULL);
}