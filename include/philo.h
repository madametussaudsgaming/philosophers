/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:06:39 by rpadasia          #+#    #+#             */
/*   Updated: 2025/06/08 15:41:28 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

/*
pthread_mutex_t, pthread_t, pthread_create, pthread_mutex_lock,
pthread_join, struct timeval
*/
struct			s_program;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					meals_eaten;
	long				last_meal_time;
	struct s_program	*program;
	pthread_mutex_t		meal_mutex;
	int					complete;
}	t_philo;

typedef struct s_program
{
	t_philo				*philos;
	int					num_of_philos;
	int					meal_needs;
	long				start_time;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					done_count;
	int					simulation_active;
	int					someone_died;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		done_count_mutex;
	pthread_mutex_t		simulation_mutex;
	pthread_mutex_t		*fork_mutexes;
}	t_program;

int				ft_atoi(const char *str);
unsigned int	get_time_ms(void);
int				validate_args(int argc, char **argv);
int				init_program(t_program *prog, int argc, char **argv);
int				init_philos_and_forks(t_program *prog);
void			cleanup(t_program *prog);
void			*monitor(void *arg);
int				check_for_deaths(t_program *prog);
void			*philo_routine(void *arg);
int				create_threads(t_program *prog);
void			join_threads(t_program *prog);
void			print_state(t_philo *philo, char *msg);
void			*exception(void *arg);
int				simulation_status(t_program *prog);
void			actionman(t_philo *philo, int first_fork, int second_fork);
void			endless(t_program *prog);
void			can_end(t_program *prog);
void			incaseofdeath(t_program *prog, int i, int now);
void			ft_usleep(long duration_ms);
void			ft_monitor_sleep(void);

#endif