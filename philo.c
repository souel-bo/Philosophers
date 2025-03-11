/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:52:12 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/11 06:50:48 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int	repeat(t_philo *philo)
{
	pthread_mutex_lock(philo->death_lock);
	if (*philo->dead_flad == 1)
		return (pthread_mutex_unlock(philo->death_lock), 1);
	pthread_mutex_unlock(philo->death_lock);
	return (0);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(700);
	return (0);
}

void	print(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->printf_lock);
	if (!repeat(philo))
	{
		time = get_time() - philo->start_time;
		printf("%zu %d %s\n", time, id, str);
	}
	pthread_mutex_unlock(philo->printf_lock);
}

void	*monitor(void *arg)
{
	t_philo	*philos;

	philos = arg;
	while (1)
		if (check_meals(philos) || check_death(philos))
			break ;
	return (NULL);
}

void	threads(t_program *program)
{
	int	i;

	i = 0;
	pthread_create(&program->monitor, NULL, &monitor, program->philos);
	while (i < program->philos[0].num_of_philos)
	{
		pthread_create(&program->philos[i].thread, NULL, &routine,
			&program->philos[i]);
		i++;
	}
	pthread_join(program->monitor, NULL);
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
}
