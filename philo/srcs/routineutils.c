/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routineutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:00:57 by rpadasia          #+#    #+#             */
/*   Updated: 2025/10/09 17:48:42 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_usleep(t_program *prog, long duration_ms)
{
	long	start;
	long	current;
	long	remaining;
	int		died;

	died = 0;
	start = get_time_ms();
	while (1)
	{
		pthread_mutex_lock(&prog->death_mutex);
		died = prog->someone_died;
		pthread_mutex_unlock(&prog->death_mutex);
		if (died)
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

int	simulation_status(t_program *prog)
{
	int	died;
	int	active;

	pthread_mutex_lock(&prog->death_mutex);
	died = prog->someone_died;
	pthread_mutex_unlock(&prog->death_mutex);
	pthread_mutex_lock(&prog->simulation_mutex);
	active = prog->simulation_active;
	pthread_mutex_unlock(&prog->simulation_mutex);
	if (died || !active)
		return (1);
	return (0);
}

int	philo_checker(t_program	*prog)
{
	int	died;

	pthread_mutex_lock(&prog->death_mutex);
	died = prog->someone_died;
	pthread_mutex_unlock(&prog->death_mutex);
	if (died)
		return (0);
	return (1);
}

int	actionman(t_philo *philo, int first_fork, int second_fork)
{
	t_program	*prog;

	prog = philo->program;
	if (!philo_checker(prog))
		return (0);
	print_state(philo, "is thinking");
	ft_usleep(prog, 1);
	pthread_mutex_lock(&prog->fork_mutexes[first_fork]);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(&prog->fork_mutexes[second_fork]);
	if (!philo_checker(prog))
	{
		pthread_mutex_unlock(&prog->fork_mutexes[second_fork]);
		pthread_mutex_unlock(&prog->fork_mutexes[first_fork]);
		return (0);
	}
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_state(philo, "is eating");
	ft_usleep(prog, prog->time_to_eat);
	return (1);
}
