/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:36:41 by rpadasia          #+#    #+#             */
/*   Updated: 2025/10/09 16:14:45 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_state(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->program->death_mutex);
	if (!(philo->program->someone_died))
	{
		pthread_mutex_lock(&philo->program->print_mutex);
		printf("%lu Philo %d %s\n", get_time_ms() - philo->program->start_time,
			philo->id + 1, msg);
		pthread_mutex_unlock(&philo->program->print_mutex);
	}
	pthread_mutex_unlock(&philo->program->death_mutex);
}

void	setforks(t_philo *philo, int *first, int *second)
{
	t_program	*prog;

	prog = philo->program;
	if (philo->id % 2 == 0)
	{
		*first = philo->id;
		*second = (philo->id + 1) % prog->num_of_philos;
	}
	else
	{
		*first = (philo->id + 1) % prog->num_of_philos;
		*second = philo->id;
	}
}

void	aftercare(t_philo *philo, int first_fork, int second_fork)
{
	t_program	*prog;

	prog = philo->program;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = LONG_MAX;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_lock(&prog->done_count_mutex);
	prog->done_count++;
	pthread_mutex_unlock(&prog->done_count_mutex);
	pthread_mutex_unlock(&prog->fork_mutexes[second_fork]);
	pthread_mutex_unlock(&prog->fork_mutexes[first_fork]);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	t_program	*prog;
	int			first_fork;
	int			second_fork;

	philo = (t_philo *)arg;
	prog = philo->program;
	setforks(philo, &first_fork, &second_fork);
	while (!prog->someone_died && prog->simulation_active)
	{
		actionman(philo, first_fork, second_fork);
		if (prog->meal_needs > 0 && philo->meals_eaten >= prog->meal_needs)
		{
			aftercare(philo, first_fork, second_fork);
			break ;
		}
		pthread_mutex_unlock(&prog->fork_mutexes[second_fork]);
		pthread_mutex_unlock(&prog->fork_mutexes[first_fork]);
		print_state(philo, "is sleeping.");
		ft_usleep(prog, prog->time_to_sleep);
	}
	return (NULL);
}
