/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:11:55 by souel-bo          #+#    #+#             */
/*   Updated: 2025/02/28 05:28:10 by souel-bo         ###   ########.fr       */
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
    pthread_t	*threads;
    unsigned long philos;
    unsigned long death;
    unsigned long eat;
    unsigned long sleep;
    unsigned long meals;
	pthread_mutex_t	protect;
    pthread_mutex_t	*mutexes;
    pthread_mutex_t	*left_fork;
    pthread_mutex_t	*right_fork;
    int id;
} t_philo;

unsigned long	ft_atoi(const char *str);
void 			initialize_thread(t_philo *threads);

#endif