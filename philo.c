/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:14:00 by souel-bo          #+#    #+#             */
/*   Updated: 2025/02/28 10:21:23 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void *routine(void *arg)
{
    t_philo *thread = (t_philo *)arg;
    
    while (1)
    {
        printf("Philo %d is thinking\n", thread->id);
        
        if (thread->id % 2 == 0)
        {   
            pthread_mutex_lock(thread->left_fork);
            printf("Philo %d has taken a fork\n", thread->id);
            pthread_mutex_lock(thread->right_fork);
            printf("Philo %d has taken a fork\n", thread->id);
        }
        else
        {
            pthread_mutex_lock(thread->right_fork);
            printf("Philo %d has taken a fork\n", thread->id);
            pthread_mutex_lock(thread->left_fork);
            printf("Philo %d has taken a fork\n", thread->id);
        }
        
        // All philosophers should eat
        printf("Philo %d is eating\n", thread->id);
        usleep(thread->eat * 1000);
        
        // All philosophers should release both forks
        pthread_mutex_unlock(thread->left_fork);
        pthread_mutex_unlock(thread->right_fork);
        
        // All philosophers should sleep after eating
        printf("Philo %d is sleeping\n", thread->id);
        usleep(thread->sleep * 1000);
    }
    
    return NULL;
}
void initialize_thread(t_philo *threads)
{
	int i = 0;
	t_philo *philos;

	pthread_mutex_init(&threads->protect, NULL);
	threads->threads = malloc(sizeof(pthread_t) * threads->philos);
	if (!threads->threads)
		return ;
	threads->mutexes = malloc(sizeof(pthread_mutex_t) * threads->philos);
	if (!threads->mutexes)
	{
		free(threads->threads);
		return ;
	}
	philos = malloc(sizeof(t_philo) * threads->philos);
	if (!philos)
	{
		free(threads->threads);
		free(threads->mutexes);
		return ;
	}
	while (i < threads->philos)
		pthread_mutex_init(&threads->mutexes[i++], NULL);
	i = 0;
	while (i < threads->philos)
	{
		philos[i] = *threads;
		philos[i].id = i + 1;
		philos[i].left_fork = &philos->mutexes[i];
		philos[i].right_fork = &philos->mutexes[(i + 1) % philos->philos];
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
