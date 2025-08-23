/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routineutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <rpadasia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:00:57 by rpadasia          #+#    #+#             */
/*   Updated: 2025/08/23 20:23:17 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_usleep(t_program *prog, long duration_ms)
{
	long	start;
	long	current;
	long	remaining;

	start = get_time_ms();
	while (1)
	{
		if (prog->someone_died)
			break ;
		current = get_time_ms();
		remaining = duration_ms - (current - start);
		if (remaining <= 0)
			break ;
		if (remaining > 10)
			usleep(5000);
		else
			usleep(200);
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
	ft_usleep(prog, prog->time_to_eat / 2);
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
	ft_usleep(prog, prog->time_to_eat);
}
