/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:36:08 by rpadasia          #+#    #+#             */
/*   Updated: 2025/05/26 21:17:18 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_state(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->write_lock);
	pthread_mutex_lock(philo->youredead);
	if (!*(philo->dead))
		printf("%u %d %s\n", get_time_ms() - philo->start_time, philo->id, msg);
	pthread_mutex_unlock(philo->youredead);
	pthread_mutex_unlock(philo->write_lock);
}

void	smart_sleep(unsigned int time_ms)
{
	unsigned int	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < time_ms)
		usleep(500);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->right);
			print_state(philo, "has taken a right fork");
			pthread_mutex_lock(philo->left);
			print_state(philo, "has taken a left fork");
		}
		else
		{
			pthread_mutex_lock(philo->left);
			print_state(philo, "has taken a left fork");
			pthread_mutex_lock(philo->right);
			print_state(philo, "has taken a right fork");
		}
		pthread_mutex_lock(philo->meal_lock);
		philo->eating = true;
		philo->last_meal = get_time_ms();
		print_state(philo, "is eating");
		pthread_mutex_unlock(philo->meal_lock);
		smart_sleep(philo->prog->time_to_eat);
		pthread_mutex_lock(philo->meal_lock);
		philo->meals_eaten += 1;
		philo->eating = false;
		if (philo->prog->must_eat_num > 0 &&
			philo->meals_eaten >= philo->prog->must_eat_num)
		{
			pthread_mutex_unlock(philo->meal_lock);
			pthread_mutex_unlock(philo->right);
			pthread_mutex_unlock(philo->left);
			break ;
		}
		pthread_mutex_unlock(philo->meal_lock);
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
		print_state(philo, "is sleeping");
		smart_sleep(philo->prog->time_to_sleep);
		print_state(philo, "is thinking");
		pthread_mutex_lock(philo->youredead);
		if (*(philo->dead))
		{
			print_state(philo, "has died!");
			pthread_mutex_unlock(philo->youredead);
			break ;
		}
		pthread_mutex_unlock(philo->youredead);
	}
	return (NULL);
}
