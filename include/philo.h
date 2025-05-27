/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:06:39 by rpadasia          #+#    #+#             */
/*   Updated: 2025/05/26 21:07:06 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
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
	bool				eating;
	int					meals_eaten;
	unsigned int		last_meal;
	unsigned int		start_time;
	pthread_mutex_t		*right;
	pthread_mutex_t		*left;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*meal_lock;
	int					*dead;
	pthread_mutex_t		*youredead;
	struct s_program	*prog;
	bool				done_eating;
}	t_philo;

typedef struct s_program
{
	int				imdead;
	int				num_of_philos;
	int				must_eat_num;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	int				philos_done;
}	t_program;

int				ft_atoi(const char *str);
int				init_program(t_program *prog, int argc, char **argv);
int				init_philos_and_forks(t_program *prog);
void			init_philos_2(t_program *prog, int *dead, pthread_mutex_t *f);
int				validate_args(int argc, char **argv);
unsigned int	get_time_ms(void);
void			*philo_routine(void *arg);
void			print_state(t_philo *philo, char *msg);
int				create_threads(t_program *prog);
void			*monitor(void *arg);
void			join_threads(t_program *prog);
void			cleanup(t_program *prog);
void			smart_sleep(unsigned int time_ms);
void			*exception(void *arg);

#endif