/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:52:12 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/10 05:33:24 by souel-bo         ###   ########.fr       */
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
		usleep(500);
	return (0);
}

void	print(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->printf_lock);
	time = get_time() - philo->start_time;
	if (!repeat(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->printf_lock);
}

void	think(t_philo *philo)
{
	print("is thinking", philo, philo->philo_id);
}

void	ft_sleep(t_philo *philo)
{
	print("is sleeping", philo, philo->philo_id);
	ft_usleep(philo->time_to_sleep);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print("has taken a fork", philo, philo->philo_id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print("has taken a fork", philo, philo->philo_id);
	philo->is_eating = 1;
	print("is eating", philo, philo->philo_id);
	pthread_mutex_lock(philo->meal);
	philo->last_meal = get_time();
	philo->meals_eated++;
	pthread_mutex_unlock(philo->meal);
	ft_usleep(philo->time_to_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}


void *routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
		ft_usleep(1);
	while (!repeat(philo))
	{
		eat(philo);
		ft_sleep(philo);
		think(philo);
	}
	return (NULL);
}

void *monitor(void *arg)
{
    t_philo *philos;
    philos = arg;
    while (1)
        if (check_meals(philos) || check_death(philos))
            break;
    return (NULL);
}

void threads(t_program *program)
{
    int i = 0;
    pthread_create(&program->monitor, NULL, &monitor, program->philos);
    while (i < program->philos[0].num_of_philos)
    {
        pthread_create(&program->philos[i].thread, NULL, &routine, &program->philos[i]);
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