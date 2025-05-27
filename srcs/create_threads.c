/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:07:09 by rpadasia          #+#    #+#             */
/*   Updated: 2025/05/27 23:45:41 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned int	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	create_threads(t_program *prog)
{
	int				i;
	unsigned int	start;

	start = get_time_ms();
	i = 0;
	if (prog->num_of_philos == 1)
	{
		prog->philos[0].start_time = start;
		prog->philos[0].last_meal = start;
		prog->philos[0].write_lock = &prog->write_lock;
		if (pthread_create(&prog->philos[0].thread, NULL,
				exception, &prog->philos[0]) != 0)
			return (0);
	}
	else
	{
		while (i < prog->num_of_philos)
		{
			prog->philos[i].start_time = start;
			prog->philos[i].last_meal = start;
			prog->philos[i].write_lock = &prog->write_lock;
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
