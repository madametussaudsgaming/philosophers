/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routineutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:00:57 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/07 18:06:49 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_usleep(long duration_ms)
{
	long	start;
	long	current;
	long	remaining;

	start = get_time_ms();
	while (1)
	{
		current = get_time_ms();
		remaining = duration_ms - (current - start);
		if (remaining <= 0)
			break ;
		if (remaining > 20)
			usleep(remaining * 800);
		else if (remaining > 5)
			usleep(1000);
		else
			usleep(100);
	}
}

// int	simulation_status(t_program *prog)
// {
// 	pthread_mutex_lock(&prog->simulation_mutex);
// 	pthread_mutex_lock(&prog->death_mutex);
// 	if (!prog->simulation_active || prog->someone_died)
// 	{
// 		pthread_mutex_unlock(&prog->simulation_mutex);
// 		pthread_mutex_unlock(&prog->death_mutex);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&prog->death_mutex);
// 	pthread_mutex_unlock(&prog->simulation_mutex);
// 	return (0);
// }

void	actionman(t_philo *philo, int first_fork, int second_fork)
{
	t_program	*prog;

	prog = philo->program;
	if (prog->someone_died)
		return ;
	print_state(philo, "is thinking");
	pthread_mutex_lock(&prog->fork_mutexes[first_fork]);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(&prog->fork_mutexes[second_fork]);
	if (prog->someone_died)
	{
		pthread_mutex_unlock(&prog->fork_mutexes[second_fork]);
		pthread_mutex_unlock(&prog->fork_mutexes[first_fork]);
		return ;
	}
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_state(philo, "is eating");
	ft_usleep(prog->time_to_eat);
}
