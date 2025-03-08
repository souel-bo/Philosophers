/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 05:57:36 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/08 04:26:07 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void init_mutex(pthread_mutex_t *forks, t_program *program)
{
    int i = 0;
    while (i < program->num_philo)
        pthread_mutex_init(&forks[i++], NULL);
}

void init_input(t_program *program, t_philo *philos, int i)
{
    philos[i].num_philo = program->num_philo;
    philos[i].num_meals = program->num_meals;
    philos[i].time_to_die = program->time_to_die;
    philos[i].time_to_eat = program->time_to_eat;
    philos[i].time_to_sleep = program->time_to_sleep;
}

void init_philo(t_program *program, t_philo *philos, pthread_mutex_t	*forks, char **argv)
{
    int i = 0;
    program->death = 0;
    while (i < program->num_philo)
    {
        philos[i].id = i + 1;
        philos[i].meals_eaten = 0;
        philos[i].dead = &program->death;
        philos[i].start_time = get_time();
        philos[i].last_meal = get_time();
        init_input(program, philos, i);
        philos[i].left_fork = &forks[i];
        if (i == 0)
             philos[i].right_fork = &forks[philos[i].num_philo - 1];
        else
            philos[i].right_fork = &forks[i - 1];
        i++;
    }
}