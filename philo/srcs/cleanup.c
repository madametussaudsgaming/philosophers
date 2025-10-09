/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:52:17 by rpadasia          #+#    #+#             */
/*   Updated: 2025/10/09 16:48:10 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	cleanup(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_of_philos)
	{
		pthread_mutex_destroy(&prog->fork_mutexes[i]);
		pthread_mutex_destroy(&prog->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&prog->print_mutex);
	pthread_mutex_destroy(&prog->death_mutex);
	pthread_mutex_destroy(&prog->simulation_mutex);
	pthread_mutex_destroy(&prog->done_count_mutex);
	free(prog->philos);
	free(prog->fork_mutexes);
}
