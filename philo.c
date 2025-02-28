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
		if (thread->id % 2 == 0)
		{	
			pthread_mutex_lock(thread->left_fork);
			printf("Philo %d take the left fork\n", thread->id);
			pthread_mutex_lock(thread->right_fork);
			printf("Philo %d take the right fork\n", thread->id);
			printf("Philo %d is eating\n", thread->id);
			usleep(thread->eat * 1000);
			pthread_mutex_unlock(thread->left_fork);
			pthread_mutex_unlock(thread->right_fork);
		}
		else if (thread->id % 2 != 0)
		{
			pthread_mutex_lock(thread->right_fork);
			printf("Philo %d take the right fork\n", thread->id);
			pthread_mutex_lock(thread->left_fork);
			printf("Philo %d take the left fork\n", thread->id);
			pthread_mutex_unlock(thread->left_fork);
			pthread_mutex_unlock(thread->right_fork);			
		}
	}
	// pthread_mutex_unlock(&thread->protect);

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
