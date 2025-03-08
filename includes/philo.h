/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:11:55 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/08 05:47:49 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <limits.h>


typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	long long num_philo;
    long long time_to_die;
    long long num_meals;
    long long time_to_sleep;
    long long time_to_eat;
	size_t			last_meal;
	size_t			current_time;
	size_t			start_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int 			*dead;
	pthread_mutex_t meal_lock;
	pthread_mutex_t death_lock;
} t_philo;


typedef struct s_program
{
	int		  		death;
	pthread_mutex_t death_lock;
	long long start;
    long long num_philo;
    long long time_to_die;
    long long num_meals;
    long long time_to_sleep;
    long long time_to_eat;
    t_philo   *philo;
} t_program ;

long long	ft_atoi(const char *str);
long long get_time(void);
void init_mutex(pthread_mutex_t *forks, t_program *program);
void destroy_mutex(pthread_mutex_t *forks, t_program *program, t_philo *philos);
void init_philo(t_program *program, t_philo *philos, pthread_mutex_t	*forks, char **argv);
void init_input(t_program *program, t_philo *philos, int i);
void create_threads(t_philo *philo, t_program *program, pthread_mutex_t *forks);

#endif
