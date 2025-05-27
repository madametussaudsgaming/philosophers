/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:14:09 by rpadasia          #+#    #+#             */
/*   Updated: 2025/05/26 20:16:59 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_program(t_program *prog, int argc, char **argv)
{
	prog->imdead = 0;
	prog->num_of_philos = ft_atoi(argv[1]);
	prog->time_to_die = ft_atoi(argv[2]);
	prog->time_to_eat = ft_atoi(argv[3]);
	prog->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		prog->must_eat_num = ft_atoi (argv[5]);
	pthread_mutex_init(&prog->write_lock, NULL);
	pthread_mutex_init(&prog->dead_lock, NULL);
	pthread_mutex_init(&prog->meal_lock, NULL);
	prog->philos = malloc(sizeof(t_philo) * prog->num_of_philos);
	prog->philos_done = 0;
	if (!prog->philos)
		return (0);
	return (1);
}

void	init_philos_2(t_program *prog, int *dead, pthread_mutex_t *f)
{
	int	i;

	i = 0;
	while (i < prog->num_of_philos)
	{
		prog->philos[i].id = i + 1;
		prog->philos[i].eating = false;
		prog->philos[i].meals_eaten = 0;
		prog->philos[i].last_meal = 0;
		prog->philos[i].start_time = 0;
		prog->philos[i].left = &f[i];
		prog->philos[i].right = &f[(i + 1) % prog->num_of_philos];
		prog->philos[i].meal_lock = &prog->meal_lock;
		prog->philos[i].dead = dead;
		prog->philos[i].youredead = &prog->dead_lock;
		prog->philos[i].prog = prog;
		prog->philos[i].done_eating = false;

		i++;
	}
}

int	init_philos_and_forks(t_program *prog)
{
	int					i;
	int					*dead_flag;
	pthread_mutex_t		*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * prog->num_of_philos);
	prog->forks = forks;
	dead_flag = &prog->imdead;
	if (!forks)
		return (0);
	while (i < prog->num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	init_philos_2(prog, dead_flag, forks);
	return (1);
}
