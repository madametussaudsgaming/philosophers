/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitorutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:07:00 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/05 22:52:02 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	can_end(t_program *prog)
{
	int			current_done_count;

	while (1)
	{
		pthread_mutex_lock(&prog->done_count_mutex);
		current_done_count = prog->done_count;
		pthread_mutex_unlock(&prog->done_count_mutex);
		if (current_done_count >= prog->num_of_philos)
		{
			pthread_mutex_lock(&prog->simulation_mutex);
			prog->simulation_active = 0;
			pthread_mutex_unlock(&prog->simulation_mutex);
			break ;
		}
		if (check_for_deaths(prog))
			break ;
		usleep(50);
	}
}

void	endless(t_program *prog)
{
	while (1)
	{
		if (check_for_deaths(prog))
			break ;
		usleep(50);
	}
}
