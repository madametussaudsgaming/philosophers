/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:45:16 by rpadasia          #+#    #+#             */
/*   Updated: 2025/05/26 20:18:32 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*monitor(void *arg)
{
	t_program	*prog;
	int			i;
	int			full_count;

	prog = (t_program *)arg;
	while (1)
	{
		i = 0;
		full_count = 0;
		while (i < prog->num_of_philos)
		{
			pthread_mutex_lock(&prog->meal_lock);
			if (!prog->philos[i].eating && get_time_ms() - prog->philos[i].last_meal > prog->time_to_die)
			{
				pthread_mutex_lock(&prog->dead_lock);
				prog->imdead = 1;
				pthread_mutex_unlock(&prog->dead_lock);
				pthread_mutex_unlock(&prog->meal_lock);
				print_state(&prog->philos[i], "died");
				return (NULL);
			}
			if (prog->must_eat_num > 0 && !prog->philos[i].done_eating && prog->philos[i].meals_eaten >= prog->must_eat_num)
			{
				prog->philos[i].done_eating = true;
				prog->philos_done++;
			}
			pthread_mutex_unlock(&prog->meal_lock);
			i++;
		}
		if (prog->must_eat_num > 0 &&
			prog->philos_done == prog->num_of_philos)
		{
			pthread_mutex_lock(&prog->dead_lock);
			prog->imdead = 1;
			pthread_mutex_unlock(&prog->dead_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
