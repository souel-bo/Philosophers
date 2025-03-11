/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 06:50:50 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/11 06:52:24 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void	think(t_philo *philo)
{
	print("is thinking", philo, philo->philo_id);
}

void	ft_sleep(t_philo *philo)
{
	print("is sleeping", philo, philo->philo_id);
	ft_usleep(philo->time_to_sleep);
}

int	check_one_philo(t_philo *philo)
{
	if (philo->num_of_philos == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print("has taken a fork", philo, philo->philo_id);
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	return (0);
}

void	help(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->is_eating = 1;
	philo->last_meal = get_time();
	print("is eating", philo, philo->philo_id);
	philo->meals_eated++;
	ft_usleep(philo->time_to_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->death_lock);
	if (*philo->finished)
		return ;
	pthread_mutex_unlock(philo->death_lock);
	if (check_one_philo(philo))
		return ;
	if (philo->philo_id % 2 != 0)
		ft_usleep(1);
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print("has taken a fork", philo, philo->philo_id);
		pthread_mutex_lock(philo->right_fork);
		print("has taken a fork", philo, philo->philo_id);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print("has taken a fork", philo, philo->philo_id);
		pthread_mutex_lock(philo->left_fork);
		print("has taken a fork", philo, philo->philo_id);
	}
	help(philo);
}
