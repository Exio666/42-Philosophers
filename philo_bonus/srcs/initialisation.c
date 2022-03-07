/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:31:34 by bsavinel          #+#    #+#             */
/*   Updated: 2022/03/03 15:20:29 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_av(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (0);
	while (i < ac)
	{
		if (!check_int(av[i]))
			return (0);
		i++;
	}
	return (1);
}

t_philo	init_philo(t_global *global)
{
	t_philo	philo;

	philo.global = global;
	philo.info = global->info;
	philo.number_of_eat = 0;
	return (philo);
}

t_info	feed_info(int ac, char **av)
{
	t_info	info;

	info.nb_philo = (int)atol(av[1]);
	info.time_to_die = (size_t)atol(av[2]);
	info.time_to_eat = (size_t)atol(av[3]);
	info.time_to_sleep = (size_t)atol(av[4]);
	info.med_time_think = info.time_to_eat - info.time_to_sleep;
	if (ac == 6)
		info.number_eat = (int)atol(av[5]);
	else
		info.number_eat = -1;
	return (info);
}

int	create_global(int ac, char **av, t_global *global)
{
	if (!check_av(ac, av))
		return (0);
	sem_unlink("fork");
	sem_unlink("start");
	sem_unlink("death");
	sem_unlink("look_fork");
	sem_unlink("print");
	global->info = feed_info(ac, av);
	global->fork = sem_open("fork", O_CREAT, 777,
			(unsigned int)global->info.nb_philo);
	global->sem_start = sem_open("start", O_CREAT, 777, 0);
	global->death = sem_open("death", O_CREAT, 777, 0);
	global->look_fork = sem_open("look_fork", O_CREAT, 777, 1);
	global->print = sem_open("print", O_CREAT, 777, 1);
	global->philo = init_philo(global);
	return (1);
}

int	launch_philo(t_global *global)
{
	int			i;
	pid_t		pid;
	t_global	launcher;

	i = 0;
	launcher = *global;
	launcher.philo.start = give_utime();
	while (i < global->info.nb_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			launcher.philo.name = i;
			routine(launcher);
			return (0);
		}
		i++;
	}
	return (1);
}
