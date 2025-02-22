/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:11:37 by souel-bo          #+#    #+#             */
/*   Updated: 2025/02/22 11:44:57 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int	check_arguments(char **arguments)
{
	int	i;
	int	j;

	i = 0;
	while (arguments[i])
	{
		j = 0;
		while (arguments[i][j])
		{
			if (arguments[i][j] < '0' && arguments[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void check_count(char **arguments)
{
	int	i;

	i = 0;
	while (arguments[i])
	{
		
	}
}

int	main(int argc, char *argv[])
{
	if (argc < 4 || argc > 6)
		return (write(2, "not enough arguments\n", 21), (1));
	if (!check_arguments(argv))
		return (write(2, "there's an invalid character in inputs\n", 40), (1));
	check_count(argv);
}
