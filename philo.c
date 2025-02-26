/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:14:00 by souel-bo          #+#    #+#             */
/*   Updated: 2025/02/26 20:56:31 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void *routine(void *arg)
{
	static int i = 1;
	t_philo *thread = (t_philo *)arg;
	pthread_mutex_lock(&thread->protect);
	printf ("hello from thread %d \n", i++);
	pthread_mutex_unlock(&thread->protect);
	return NULL;
}

void	initialize_thread(t_philo *threads)
{
	int i = 0;
	pthread_mutex_init(&threads->protect, NULL);
	threads->threads = malloc(sizeof(pthread_t) * threads->philos);
	if (!threads->threads)
		return ;
	while (i < threads->philos)
	{
		pthread_create(&threads->threads[i], NULL, routine, (void *)threads);
		i++;
	}
	i = 0;
	while (i < threads->philos)
	{
		pthread_join(threads->threads[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&threads->protect);
}