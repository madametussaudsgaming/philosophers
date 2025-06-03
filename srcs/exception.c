/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 00:44:38 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/04 00:37:48 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*exception(void *arg)
{
	t_philo			*philo;
	t_program		*prog;

	philo = (t_philo *)arg;
	prog = philo->program;
	print_state(philo, "is thinking");
	pthread_mutex_lock(&prog->fork_mutexes[0]);
	print_state(philo, "has taken a fork");
	usleep(prog->time_to_die * 1000);
	pthread_mutex_unlock(&prog->fork_mutexes[0]);
	return (NULL);
}
