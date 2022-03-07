/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:29:31 by bsavinel          #+#    #+#             */
/*   Updated: 2022/03/03 15:23:51 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <semaphore.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

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
	int		nb_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		number_eat;
	size_t	med_time_think;
}	t_info;

typedef struct s_philo
{
	int				name;
	t_info			info;
	size_t			start;
	int				number_of_eat;
	size_t			date_of_death;
	struct s_global	*global;
}	t_philo;

typedef struct s_global
{
	sem_t	*death;
	sem_t	*sem_start;
	sem_t	*fork;
	sem_t	*look_fork;
	sem_t	*print;
	t_info	info;
	t_philo	philo;
}	t_global;

/*
 *	death_end.c
 */

int				check_death(t_philo *philo);
void			modifier_death(t_philo *philo);
int				good_end(t_global *global);
int				exit_no_arg(void);

/*
 *	initialisation.c
 */

int				check_av(int ac, char **av);
t_philo			init_philo(t_global *global);
t_info			feed_info(int ac, char **av);
int				create_global(int ac, char **av, t_global *global);
int				launch_philo(t_global *global);

/*
 *	philo_mini_utils.c
 */

int				ft_strlen(const char *s);
int				ft_isdigit(int c);
int				ft_isspace(char c);
size_t			give_utime(void);
void			_usleep(size_t time, t_global *global);

/*
 *	philo_utils.c
 */

int				check_int(char *str);
long int		ft_atol(const char *nptr);
void			printer_sem(t_philo *philo, sem_t *sem, int name, char *str);
void			take_fork(t_philo *philo);
void			drop_fork(t_philo *philo);

/*
 *	routine.c
 */

void			routine(t_global global);
void			start_eat(t_philo *philo);
void			start_sleep(t_philo *philo);

#endif