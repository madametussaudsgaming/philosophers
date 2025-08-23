/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <rpadasia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:45:16 by rpadasia          #+#    #+#             */
/*   Updated: 2025/08/23 18:57:10 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	incaseofdeath(t_program *prog, int i, long now)
{
	int	id;

	prog->someone_died = 1;
	pthread_mutex_lock(&prog->print_mutex);
	id = prog->philos[i].id + 1;
	printf("%ld %d has died\n", now - prog->start_time, id);
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
			pthread_mutex_lock(&prog->death_mutex);
			if (!prog->someone_died)
				incaseofdeath(prog, i, now);
			pthread_mutex_unlock(&prog->death_mutex);
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
