/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:11:55 by souel-bo          #+#    #+#             */
/*   Updated: 2025/02/22 16:11:20 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct s_philo
{
    //number_of_philosophers//////time_to_die/////time_to_eat/////////time_to_sleep/////[number_of_times_each_philosopher_must_eat]
    unsigned long philos;
    unsigned long death;
    unsigned long eat;
    unsigned long sleep;
    unsigned long meals;
} t_philo;

unsigned long	ft_atoi(const char *str);

#endif