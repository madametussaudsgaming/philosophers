/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:36:41 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/03 18:04:16 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_state(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->program->print_mutex);
	pthread_mutex_lock(&philo->program->death_mutex);
	if (!(philo->program->someone_died))
	{
		printf("%lu Philo %d %s\n", get_time_ms() - philo->program->start_time,
			philo->id + 1, msg);
	}
	pthread_mutex_unlock(&philo->program->death_mutex);
	pthread_mutex_unlock(&philo->program->print_mutex);
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
	pthread_mutex_lock(&prog->done_count_mutex);
	prog->done_count++;
	pthread_mutex_unlock(&prog->done_count_mutex);
	pthread_mutex_unlock(&philo->meal_mutex);
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
	while (1)
	{
		if (simulation_status(prog))
			break ;
		actionman(philo, first_fork, second_fork);
		if (prog->meal_needs > 0 && philo->meals_eaten >= prog->meal_needs)
		{
			aftercare(philo, first_fork, second_fork);
			break ;
		}
		pthread_mutex_unlock(&philo->meal_mutex);
		pthread_mutex_unlock(&prog->fork_mutexes[second_fork]);
		pthread_mutex_unlock(&prog->fork_mutexes[first_fork]);
		print_state(philo, "is sleeping.");
		usleep(prog->time_to_sleep * 1000);
	}
	return (NULL);
}
