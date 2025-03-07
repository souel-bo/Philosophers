/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:11:37 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/07 06:44:36 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int parse_input(char **argv, t_program *program, int arguments)
{
		if (arguments == 6)
		{
			program->num_meals = ft_atoi(argv[5]);
			if (program->num_meals == 9999999999999 || program->num_meals == 0)
				return (0);
		}
		else 
			program->num_meals = -1;
		program->num_philo = ft_atoi(argv[1]);
		program->time_to_die = ft_atoi(argv[1]);
		program->time_to_eat = ft_atoi(argv[3]);
		program->time_to_sleep = ft_atoi(argv[4]);
		if (program->time_to_die == 9999999999999)
			return (0);
		if (program->time_to_sleep == 9999999999999 || program->time_to_sleep == 0)
			return (0);
		if (program->time_to_eat == 9999999999999 || program->time_to_eat == 0)
			return (0);
		if (program->num_philo == 9999999999999 || program->num_philo == 0 ||  program->num_philo > 200)
			return (0);
		return (1);
}

int	main(int argc, char *argv[])
{
	t_program program;
	t_philo philos[200];
	pthread_mutex_t forks[200];
	if (argc != 5 && argc != 6)
		return (1);
	if (!parse_input(argv, &program, argc))
		return (1);
	init_mutex(forks, &program);
	init_philo();
	destroy_mutex(forks, &program);
}
