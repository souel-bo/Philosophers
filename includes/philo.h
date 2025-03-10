/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:11:55 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/10 21:33:03 by souel-bo         ###   ########.fr       */
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
#include <stdbool.h>
typedef struct s_philo
{
	size_t time_to_eat;
	int philo_id;
	size_t time_to_die;
	int is_eating;
	int meals_eated;
	pthread_t thread;
	size_t last_meal;
	size_t time_to_sleep;
	size_t start_time;
	int num_of_philos;
	int num_meals;
	int *dead_flad;
	int     *finished;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *printf_lock;
	pthread_mutex_t *death_lock;
	pthread_mutex_t *meal;
	pthread_mutex_t meal_lock;
} t_philo ;

typedef struct s_program
{
	int dead_flag;
	int finished;
	pthread_mutex_t printf_lock;
	pthread_mutex_t death_lock;
	pthread_mutex_t meal;
	pthread_t monitor;
	t_philo *philos;
} t_program;

long long	ft_atoi(const char *str);
void init_program(t_program *program, t_philo *philos);
void  init_threads(t_philo *philos, t_program *program, pthread_mutex_t *forks, char **argv);
size_t get_time(void);
void init_mutexes(pthread_mutex_t *forks, int number_of_philos);
void destroy_mutexes(t_program *program, t_philo *philos, pthread_mutex_t *forks);
void threads(t_program *program);
int check_meals(t_philo *philos);
void *monitor(void *arg);
int check_death(t_philo *philos);
void	print(char *str, t_philo *philo, int id);

#endif
