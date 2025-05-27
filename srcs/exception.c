/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 00:44:38 by rpadasia          #+#    #+#             */
/*   Updated: 2025/05/28 00:09:10 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*exception(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->prog->must_eat_num <= 0)
		return (NULL);
	pthread_mutex_lock(philo->left);
	print_state(philo, "has taken a fork");
	while (1)
	{
		philo->eating = true;
		philo->last_meal = get_time_ms();
		print_state(philo, "is eating");
		philo->meals_eaten++;
		philo->eating = false;
		if (philo->meals_eaten >= philo->prog->must_eat_num)
		{
			pthread_mutex_unlock(philo->left);
			break ;
		}
		pthread_mutex_unlock(philo->left);
		if (*(philo->dead))
			break ;
	}
	return (NULL);
}
