/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:11:37 by souel-bo          #+#    #+#             */
/*   Updated: 2025/02/22 16:15:47 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

t_philo *check_count(char **arguments, int argc)
{
	t_philo	*content;

	content = malloc(sizeof(t_philo));
	if (!content)
		return (NULL);
	content->philos = ft_atoi(arguments[1]);
	if ( content->philos == 0 || content->philos > 2147483647)
	{
		free(content);
		return NULL;
	}
	content->death = ft_atoi(arguments[2]);
	if (content->death == 9999999999999 || content->death == 0 || content->death > 2147483647)
	{
		free(content);
		return NULL;
	}
	content->eat = ft_atoi(arguments[3]);
	if (content->eat == 9999999999999 || content->eat == 0 || content->eat > 2147483647)
	{
		free(content);
		return NULL;
	}
	content->sleep = ft_atoi(arguments[4]);
	if (content->sleep == 9999999999999 || content->sleep == 0 || content->sleep > 2147483647)
	{
		free(content);
		return NULL;
	}
	if (argc == 6)
	{
		content->meals = ft_atoi(arguments[5]);
		if (content->meals == 9999999999999 || content->meals == 0 || content->meals > 2147483647)
		{
			free(content);
			return NULL;
		}
	}
	return content;
}

int	main(int argc, char *argv[])
{
	t_philo *threads;
	if (argc < 4 || argc > 6)
		return (write(2, "not enough arguments\n", 21), (1));
	threads = check_count(argv, argc);
	if (!threads)
	{
		printf("failed");
		return (1);
	}
	else
	{
		printf("success");
		free(threads);
		return (0);
	}
}
