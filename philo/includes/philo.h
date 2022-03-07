/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:29:31 by bsavinel          #+#    #+#             */
/*   Updated: 2022/03/03 15:10:54 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <string.h>

# define LIST_OF_ARG "./philo time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]"
# define TAKE_FORK "has taken a fork"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define THINK "is thinking"

/*
 *	Structure
 */

typedef struct s_info
{
	int			nb_philo;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			number_eat;
}	t_info;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				take;
}	t_fork;

typedef struct s_philo
{
	int				name;
	t_fork			*fork_left;
	t_fork			*fork_right;
	struct s_global	*global;
	size_t			date_of_death;
	t_info			info;
	int				number_of_eat;
	size_t			start;
}	t_philo;

typedef struct s_global
{
	size_t			start_philo;
	pthread_mutex_t	mutt_death;
	pthread_mutex_t	mutt_print;
	int				death;
	t_info			info;
	t_fork			*tab_fork;
	size_t			time_start;
	pthread_t		*tab_pthread;
	t_philo			*tab_philo;
}	t_global;

/*
 *	death.c
 */

int				check_death(t_philo *philo, pthread_mutex_t *muttex);
int				check_death_global(t_global *global, pthread_mutex_t *muttex);
void			modifier_death(t_philo *philo, pthread_mutex_t *muttex,
					int value);

/*
 *	end_tools.c
 */

int				destruc_fork(t_global *global, int nb_fork);
int				fusion_philo(t_global *global, int nb_philo);

/*
 *	end.c
 */

int				good_end(t_global *global);
int				exit_no_tab_philo(t_global *global);
int				exit_no_arg(void);
int				exit_time_or_mutex(void);

/*
 *	init_struct.c
 */

int				check_av(int ac, char **av);
t_info			feed_info(int ac, char **av);
t_fork			*creation_tab_fork(t_global *global);
t_global		*create_global(int ac, char **av);
int				creation_tab_philo(t_global *global);

/*
 *	philo_mini_utils.c
 */

int				ft_strlen(const char *s);
int				ft_isdigit(int c);
int				ft_isspace(char c);
size_t			give_utime(void);
void			_usleep(size_t time, t_philo *philo);

/*
 *	philo_utils.c
 */

int				check_int(char *str);
long int		ft_atol(const char *nptr);
void			printer_mutex(t_philo *philo, pthread_mutex_t *muttex,
					int name, char *str);

/*
 *	routine.c
 */

void			*routine(void *structure);
void			start_eat(t_philo *philo);
void			start_sleep(t_philo *philo);
int				launch_philo(t_global *global);

/*
 *	take_and_drop.c
 */

void			take_right(t_philo *philo);
void			take_left(t_philo *philo);
void			take_fork(t_philo *philo);
void			drop_fork(t_philo *philo);

#endif