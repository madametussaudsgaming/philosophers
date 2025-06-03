/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routineutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:00:57 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/03 18:04:22 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	simulation_status(t_program *prog)
{
	pthread_mutex_lock(&prog->simulation_mutex);
	pthread_mutex_lock(&prog->death_mutex);
	if (!prog->simulation_active || prog->someone_died)
	{
		pthread_mutex_unlock(&prog->simulation_mutex);
		pthread_mutex_unlock(&prog->death_mutex);
		return (1);
	}
	return (0);
}

void	actionman(t_philo *philo, int first_fork, int second_fork)
{
	t_program	*prog;

	prog = philo->program;
	pthread_mutex_unlock(&prog->simulation_mutex);
	pthread_mutex_unlock(&prog->death_mutex);
	print_state(philo, "is thinking");
	pthread_mutex_lock(&prog->fork_mutexes[first_fork]);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(&prog->fork_mutexes[second_fork]);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	usleep(prog->time_to_eat * 1000);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
}
