/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:03:19 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/08 05:56:05 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void *check(void *arg)
{
    t_philo *philos = arg;
    int i;

    while (1)
    {
        i = 0;
        while (i < philos[0].num_philo)
        {
            pthread_mutex_lock(&philos[i].meal_lock);
            if (get_time() - philos[i].last_meal > philos[i].time_to_die)
            {
                printf("Philosopher %d died\n", philos[i].id);

                pthread_mutex_lock(&philos[i].death_lock);
                *philos[i].dead = 1;
                pthread_mutex_unlock(&philos[i].death_lock);

                pthread_mutex_unlock(&philos[i].meal_lock);
                return NULL;
            }
            pthread_mutex_unlock(&philos[i].meal_lock);
            i++;
        }
    }

    return NULL;
}

int check_dead(t_philo *philos) 
{
    pthread_mutex_lock(&philos->death_lock);
    if (*philos->dead == 1)
    {
        pthread_mutex_unlock(&philos->death_lock);
        return 1;
    }
    pthread_mutex_unlock(&philos->death_lock);
    return 0;   
}

void *routine(void *arg)
{
    t_philo *philos = arg;
    while (!check_dead(philos))
    {
        printf("%lld philo %d is thinking\n", get_time() - philos->start_time, philos->id);
        if (philos->id % 2 == 0)
        {
            pthread_mutex_lock(philos->right_fork);
            printf("%lld philo %d has taken the right fork\n", get_time() - philos->start_time, philos->id);
            pthread_mutex_lock(philos->left_fork);
            printf("%lld philo %d has taken the left fork\n", get_time() - philos->start_time, philos->id);
            pthread_mutex_unlock(philos->right_fork);
            pthread_mutex_unlock(philos->left_fork);
        }
        else if (philos->id % 2 != 0)
        {
            pthread_mutex_lock(philos->left_fork);
            printf("%lld philo %d has taken the left fork\n", get_time() - philos->start_time, philos->id);
            pthread_mutex_lock(philos->right_fork);
            printf("%lld philo %d has taken the right fork\n", get_time() - philos->start_time, philos->id);
            pthread_mutex_unlock(philos->right_fork);
            pthread_mutex_unlock(philos->left_fork);
        }
        printf("daba sh7al = %lld\n", get_time());
        printf("%lld philo %d is eating\n", get_time() - philos->start_time, philos->id);
        usleep(philos->time_to_eat * 1000);
        pthread_mutex_lock(&philos->meal_lock);
        philos->last_meal = get_time();
        pthread_mutex_unlock(&philos->meal_lock);
        if (check_dead(philos))
            break;
        printf("%lld philo %d is sleeping\n", get_time() - philos->start_time, philos->id);
        usleep(philos->time_to_sleep * 1000);
    }
    return NULL;
}

void create_threads(t_philo *philo, t_program *program, pthread_mutex_t *forks)
{
    pthread_t monitor;
    pthread_create(&monitor, NULL, check, (void *)philo);

    int i = 0;
    while (i < program->num_philo)
    {
        pthread_create(&philo[i].thread, NULL, routine, (void*)&philo[i]);
        i++;
    }
    i = 0;
    while (i < program->num_philo)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
    pthread_join(monitor, NULL);
}
