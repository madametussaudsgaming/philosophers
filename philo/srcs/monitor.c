/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:45:16 by rpadasia          #+#    #+#             */
/*   Updated: 2025/10/09 16:48:23 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	incaseofdeath(t_program *prog, int i, long now)
{
	pthread_mutex_lock(&prog->death_mutex);
	prog->someone_died = 1;
	pthread_mutex_unlock(&prog->death_mutex);
	pthread_mutex_lock(&prog->print_mutex);
	printf("%ld %d has died\n", now - prog->start_time, prog->philos[i].id + 1);
	pthread_mutex_unlock(&prog->print_mutex);
}

int	check_for_deaths(t_program *prog)
{
	int		i;
	long	now;
	long	last_meal;

	i = 0;
	while (i < prog->num_of_philos)
	{
		now = get_time_ms();
		pthread_mutex_lock(&prog->philos[i].meal_mutex);
		last_meal = prog->philos[i].last_meal_time;
		pthread_mutex_unlock(&prog->philos[i].meal_mutex);
		if (now - last_meal > prog->time_to_die)
		{
			if (!prog->someone_died)
				incaseofdeath(prog, i, now);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_program	*prog;

	prog = (t_program *)arg;
	if (prog->meal_needs > 0)
	{
		can_end(prog);
	}
	else
	{
		endless(prog);
	}
	pthread_mutex_lock(&prog->simulation_mutex);
	prog->simulation_active = 0;
	pthread_mutex_unlock(&prog->simulation_mutex);
	return (NULL);
}
