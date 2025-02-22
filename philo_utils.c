/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:28:47 by souel-bo          #+#    #+#             */
/*   Updated: 2025/02/22 11:38:53 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

unsigned long	ft_atoi(const char *str)
{
	int		i;
	int		s;
	int		r;

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
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		r = r * 10 + str[i] - '0';
		i++;
	}
	return (r * s);
}
