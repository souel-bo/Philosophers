/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:14:00 by souel-bo          #+#    #+#             */
/*   Updated: 2025/02/27 05:55:52 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void *routine(void *arg)
{
	t_philo *thread = (t_philo *)arg;

	pthread_mutex_lock(&thread->protect);
	if (thread->id % 2 == 0)
	{
		printf("id : %d\n", thread->id);
		printf("hello from thread %d\n", thread->id); // Use thread->id instead of shared static i
	}
	else if (thread->id % 2 != 0)
		printf("is thinking\n");
	pthread_mutex_unlock(&thread->protect);

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
		philos[i] = *threads;  // Copy base structure
		philos[i].id = i + 1;  // Assign unique ID
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
