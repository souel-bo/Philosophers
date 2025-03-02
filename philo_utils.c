/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfyn <sfyn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:28:47 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/01 23:25:50 by sfyn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

unsigned long	ft_atoi(const char *str)
{
	unsigned long		i;
	unsigned long		s;
	unsigned long		r;

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
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			r = r * 10 + str[i] - '0';
		else 
			return 9999999999999;
		i++;
	}
	return (r * s);
}

long long get_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000LL + time.tv_usec / 1000LL);
}