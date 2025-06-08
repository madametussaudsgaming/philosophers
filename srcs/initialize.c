/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:14:09 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/08 15:32:48 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_program(t_program *prog, int argc, char **argv)
{
	prog->done_count = 0;
	prog->simulation_active = 1;
	prog->someone_died = 0;
	prog->start_time = (long)get_time_ms();
	prog->num_of_philos = ft_atoi(argv[1]);
	prog->time_to_die = ft_atoi(argv[2]);
	prog->time_to_eat = ft_atoi(argv[3]);
	prog->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		prog->meal_needs = ft_atoi (argv[5]);
	else
		prog->meal_needs = -1;
	pthread_mutex_init(&prog->print_mutex, NULL);
	pthread_mutex_init(&prog->death_mutex, NULL);
	pthread_mutex_init(&prog->simulation_mutex, NULL);
	pthread_mutex_init(&prog->done_count_mutex, NULL);
	prog->philos = malloc(sizeof(t_philo) * prog->num_of_philos);
	if (!prog->philos)
		return (0);
	return (1);
}

void	init_philos_2(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_of_philos)
	{
		prog->philos[i].id = i;
		prog->philos[i].meals_eaten = 0;
		prog->philos[i].last_meal_time = prog->start_time;
		prog->philos[i].program = prog;
		prog->philos[i].complete = 0;
		pthread_mutex_init(&prog->philos[i].meal_mutex, NULL);
		i++;
	}
}

int	init_philos_and_forks(t_program *prog)
{
	int					i;
	pthread_mutex_t		*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * prog->num_of_philos);
	prog->fork_mutexes = forks;
	if (!forks)
		return (0);
	while (i < prog->num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	init_philos_2(prog);
	return (1);
}
