/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 06:49:52 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/11 06:11:42 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void	init_program(t_program *program, t_philo *philos)
{
	program->philos = philos;
	pthread_mutex_init(&program->printf_lock, NULL);
	pthread_mutex_init(&program->death_lock, NULL);
	pthread_mutex_init(&program->meal, NULL);
	program->dead_flag = 0;
	program->finished = 0;
}

void	init_mutexes(pthread_mutex_t *forks, int number_of_philos)
{
	int	i;

	i = 0;
	while (i < number_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	store_input(t_philo *philo, char **arguments)
{
	philo->num_of_philos = ft_atoi(arguments[1]);
	philo->time_to_die = ft_atoi(arguments[2]);
	philo->time_to_eat = ft_atoi(arguments[3]);
	philo->time_to_sleep = ft_atoi(arguments[4]);
	if (arguments[5])
		philo->num_meals = ft_atoi(arguments[5]);
	else
		philo->num_meals = -1;
}

void	init_threads(t_philo *philos, t_program *program,
		pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philos[i].philo_id = i + 1;
		philos[i].is_eating = 0;
		philos[i].meals_eated = 0;
		store_input(&philos[i], argv);
		philos[i].start_time = get_time();
		philos[i].last_meal = get_time();
		philos[i].printf_lock = &program->printf_lock;
		philos[i].meal = &program->meal;
		pthread_mutex_init(&philos[i].meal_lock, NULL);
		philos[i].death_lock = &program->death_lock;
		philos[i].dead_flad = &program->dead_flag;
		philos[i].finished = &program->dead_flag;
		philos[i].left_fork = &forks[i];
		if (i == 0)
			philos[i].right_fork = &forks[philos[i].num_of_philos - 1];
		else
			philos[i].right_fork = &forks[i - 1];
		i++;
	}
}
