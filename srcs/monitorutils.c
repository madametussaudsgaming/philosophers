/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitorutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:07:00 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/03 19:09:47 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	can_end(t_program *prog)
{
	int			someone_died;
	int			current_done_count;

	pthread_mutex_lock(&prog->done_count_mutex);
	current_done_count = prog->done_count;
	pthread_mutex_unlock(&prog->done_count_mutex);
	pthread_mutex_lock(&prog->death_mutex);
	someone_died = prog->someone_died;
	pthread_mutex_unlock(&prog->death_mutex);
	while (current_done_count < prog->num_of_philos && !someone_died)
	{
		check_for_deaths(prog);
		usleep(1000);
		pthread_mutex_lock(&prog->done_count_mutex);
		current_done_count = prog->done_count;
		pthread_mutex_unlock(&prog->done_count_mutex);
		pthread_mutex_lock(&prog->death_mutex);
		someone_died = prog->someone_died;
		pthread_mutex_unlock(&prog->death_mutex);
	}
}

void	endless(t_program *prog)
{
	int			someone_died;
	int			current_done_count;

	pthread_mutex_lock(&prog->death_mutex);
	someone_died = prog->someone_died;
	pthread_mutex_unlock(&prog->death_mutex);
	while (!someone_died)
	{
		check_for_deaths(prog);
		usleep(1000);
		pthread_mutex_lock(&prog->death_mutex);
		someone_died = prog->someone_died;
		pthread_mutex_unlock(&prog->death_mutex);
	}
}

void	incaseofdeath(t_program *prog, int i, int id, int now)
{
	prog->someone_died = 1;
	pthread_mutex_lock(&prog->print_mutex);
	id = prog->philos[i].id + 1;
	printf("%ld %d has died\n", now - prog->start_time, id);
	pthread_mutex_unlock(&prog->print_mutex);
}
