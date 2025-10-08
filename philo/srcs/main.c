/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <rpadasia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:34:03 by rpadasia          #+#    #+#             */
/*   Updated: 2025/09/15 12:37:35 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char *argv[])
{
	t_program		program;
	pthread_t		monitor_thread;

	if (!validate_args(argc, argv))
		return (1);
	if (!init_program(&program, argc, argv))
		return (1);
	if (!init_philos_and_forks(&program))
		return (1);
	if (!create_threads(&program))
		return (1);
	if (pthread_create(&monitor_thread, NULL, monitor, &program) != 0)
		return (1);
	pthread_join(monitor_thread, NULL);
	join_threads(&program);
	cleanup(&program);
	return (0);
}
