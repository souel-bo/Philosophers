/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfyn <sfyn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:14:00 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/01 23:42:25 by sfyn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

long get_elapsed_time(long long start_time)
{
    return get_time() - start_time;  // Get the elapsed time for the philosopher
}

void *routine(void *arg)
{
    t_philo *thread = (t_philo *)arg;
    thread->simulation_time = get_time();
    if (thread->arguments == 6)
    {
        while (thread->meals > 0)
        {
            printf("%ld Philo %d is thinking\n", get_elapsed_time(thread->simulation_time), thread->id);
        
            if (thread->id % 2 == 0)
            {   
                pthread_mutex_lock(thread->left_fork);
                printf("%ld Philo %d has taken a left fork\n", get_elapsed_time(thread->simulation_time), thread->id);
                pthread_mutex_lock(thread->right_fork);
                printf("%ld Philo %d has taken a right fork\n", get_elapsed_time(thread->simulation_time), thread->id);
            }
            else
            {
                pthread_mutex_lock(thread->right_fork);
                printf("%ld Philo %d has taken a right fork\n", get_elapsed_time(thread->simulation_time), thread->id);
                pthread_mutex_lock(thread->left_fork);
                printf("%ld Philo %d has taken a left fork\n", get_elapsed_time(thread->simulation_time), thread->id);
            }
            printf("%ld Philo %d is eating\n", get_elapsed_time(thread->simulation_time), thread->id);
            usleep(thread->eat * 1000);
            pthread_mutex_unlock(thread->left_fork);
            pthread_mutex_unlock(thread->right_fork);
            printf("%ld Philo %d is sleeping\n", get_elapsed_time(thread->simulation_time), thread->id);
            usleep(thread->sleep * 1000);
            thread->meals--;
        }
        return NULL;
    }
    else
    {
        while (1)
        {
            printf("%ld Philo %d is thinking\n", get_elapsed_time(thread->simulation_time), thread->id); 
            if (thread->id % 2 == 0)
            {   
                pthread_mutex_lock(thread->left_fork);
                printf("%ld Philo %d has taken a left fork\n", get_elapsed_time(thread->simulation_time), thread->id);
                pthread_mutex_lock(thread->right_fork);
                printf("%ld Philo %d has taken a right fork\n", get_elapsed_time(thread->simulation_time), thread->id);
            }
            else
            {
                pthread_mutex_lock(thread->right_fork);
                printf("%ld Philo %d has taken a right fork\n", get_elapsed_time(thread->simulation_time), thread->id);
                pthread_mutex_lock(thread->left_fork);
                printf("%ld Philo %d has taken a left fork\n", get_elapsed_time(thread->simulation_time), thread->id);
            }
            printf("%ld Philo %d is eating\n", get_elapsed_time(thread->simulation_time), thread->id);
            usleep(thread->eat * 1000);
            pthread_mutex_unlock(thread->left_fork);
            pthread_mutex_unlock(thread->right_fork);
            printf("%ld Philo %d is sleeping\n", get_elapsed_time(thread->simulation_time), thread->id);
            usleep(thread->sleep * 1000);
        }
    }
    return NULL;
}


void initialize_thread(t_philo *threads, int arguments)
{
    int i = 0;
    t_philo *philos;

    threads->arguments = arguments;
    pthread_mutex_init(&threads->protect, NULL);
    threads->threads = malloc(sizeof(pthread_t) * threads->philos);
    if (!threads->threads)
        return;
    threads->mutexes = malloc(sizeof(pthread_mutex_t) * threads->philos);
    if (!threads->mutexes)
    {
        free(threads->threads);
        return;
    }
    philos = malloc(sizeof(t_philo) * threads->philos);
    if (!philos)
    {
        free(threads->threads);
        free(threads->mutexes);
        return;
    }
    
    while (i < threads->philos)
        pthread_mutex_init(&threads->mutexes[i++], NULL);
    
    i = 0;
    while (i < threads->philos)
    {
        philos[i] = *threads;
        philos[i].id = i + 1;
        philos[i].left_fork = &threads->mutexes[i];
        philos[i].right_fork = &threads->mutexes[(i + 1) % threads->philos];
        pthread_create(&threads->threads[i], NULL, routine, (void *)&philos[i]);
        i++;
    }
    
    i = 0;
    while (i < threads->philos)
        pthread_join(threads->threads[i++], NULL);
    
    i = 0;
    while (i < threads->philos)
        pthread_mutex_destroy(&threads->mutexes[i++]);
    
    pthread_mutex_destroy(&threads->protect);
    free(philos);
}