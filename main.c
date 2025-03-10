/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:11:37 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/10 08:39:00 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int parse_input(char **argv, int arguments)
{
		if (arguments == 6)
		{
			if (ft_atoi(argv[5]) == 9999999999999 || ft_atoi(argv[5]) == 0)
				return (0);
		}
		if (ft_atoi(argv[4]) == 9999999999999 || ft_atoi(argv[4]) == 0)
			return (0);
		if (ft_atoi(argv[2]) == 9999999999999 )
			return (0);
		if (ft_atoi(argv[3]) == 9999999999999 || ft_atoi(argv[3]) == 0)
			return (0);
		if (ft_atoi(argv[1]) == 9999999999999 || ft_atoi(argv[1]) == 0 ||  ft_atoi(argv[1]) > 200)
			return (0);
		return (1);
}

int main(int argc, char **argv)
{
	t_program program;
	t_philo philos[200];
	pthread_mutex_t forks[200];
	
	if (argc < 5 || argc > 6)
		return (1);
	if (!parse_input(argv, argc))
		return (1);
	init_program(&program, philos);
	init_mutexes(forks, ft_atoi(argv[1]));
	init_threads(philos, &program, forks, argv);
	threads(&program);
	destroy_mutexes(&program, philos, forks);
}




