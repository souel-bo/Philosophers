/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:28:47 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/09 08:43:31 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

long long	ft_atoi(const char *str)
{
	unsigned long		i;
	unsigned long		s;
	unsigned long		r;

	i = 0;
	s = 1;
	r = 0;
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return 9999999999999;
		i++;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			r = r * 10 + str[i] - '0';
		else 
			return 9999999999999;
		i++;
	}
	if (r > INT_MAX)
		return 9999999999999; 
	return (r * s);
}

void destroy_mutexes(t_program *program, t_philo *philos, pthread_mutex_t *forks)
{
	int i = 0;
	pthread_mutex_destroy(&program->printf_lock);
	pthread_mutex_destroy(&program->meal);
	pthread_mutex_destroy(&program->death_lock);
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

size_t get_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000LL + time.tv_usec / 1000LL);
}