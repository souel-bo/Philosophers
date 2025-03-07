/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:11:37 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/07 05:00:00 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int	main(int argc, char *argv[])
{
	t_program program;
	t_philo philos[200];
	pthread_mutex_t forks[200];
	if (argc != 5 && argc != 6)
		return (1);
	if (!parse_input(argv, &program))
		return (1);
}
