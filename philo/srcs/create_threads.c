/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <rpadasia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:07:09 by rpadasia          #+#    #+#             */
/*   Updated: 2025/10/08 15:39:35 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	create_threads(t_program *prog)
{
	int				i;

	i = 0;
	prog->start_time = get_time_ms();
	if (prog->num_of_philos == 1)
	{
		prog->philos[i].last_meal_time = prog->start_time;
		if (pthread_create(&prog->philos[0].thread, NULL,
				exception, &prog->philos[0]) != 0)
			return (0);
	}
	else
	{
		while (i < prog->num_of_philos)
		{
			prog->philos[i].last_meal_time = prog->start_time;
			if (pthread_create(&prog->philos[i].thread, NULL,
					philo_routine, &prog->philos[i]) != 0)
				return (0);
			i++;
		}
	}
	return (1);
}

void	join_threads(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_of_philos)
	{
		pthread_join(prog->philos[i].thread, NULL);
		i++;
	}
}
