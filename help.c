/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 06:18:14 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/11 06:18:32 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int	check(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (!philo->is_eating && get_time() - philo->last_meal >= time_to_die
		&& philo->is_eating == 0)
		return (pthread_mutex_unlock(&philo->meal_lock), 1);
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

int	check_death(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if (check(&philos[i], philos[i].time_to_die))
		{
			print("dead", &philos[i], philos[i].philo_id);
			pthread_mutex_lock(philos[0].death_lock);
			*philos->dead_flad = 1;
			pthread_mutex_unlock(philos[0].death_lock);
			return (1);
		}
		i++;
	}
	return (0);
}
