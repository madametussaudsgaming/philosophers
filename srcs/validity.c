/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:55:35 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/02 21:22:16 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	arg_scanner(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf ("./philo philo_num time_die time_eat time_sleep [nbr_meals]\n");
		return (0);
	}
	i = 0;
	while (++i < argc)
	{
		if (!arg_scanner(argv[i]) || ft_atoi(argv[i]) <= 0)
		{
			printf ("INTEGERS ONLY\n");
			return (0);
		}
	}
	return (1);
}
