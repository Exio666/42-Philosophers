/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:31:34 by bsavinel          #+#    #+#             */
/*   Updated: 2022/03/03 15:06:50 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

t_info	feed_info(int ac, char **av)
{
	t_info	info;

	info.nb_philo = (int)atol(av[1]);
	info.time_to_die = (size_t)atol(av[2]);
	info.time_to_eat = (size_t)atol(av[3]);
	info.time_to_sleep = (size_t)atol(av[4]);
	if (ac == 6)
		info.number_eat = (int)atol(av[5]);
	else
		info.number_eat = -1;
	return (info);
}

t_fork	*creation_tab_fork(t_global *global)
{
	t_fork	*tab_fork;
	int		i;

	i = 0;
	tab_fork = malloc(sizeof(t_fork) * global->info.nb_philo);
	if (!tab_fork)
		return (NULL);
	memset(tab_fork, 0, sizeof(t_fork) * global->info.nb_philo);
	while (i < global->info.nb_philo)
	{
		tab_fork[i].take = 0;
		pthread_mutex_init(&tab_fork[i].fork, NULL);
		i++;
	}
	return (tab_fork);
}

t_global	*create_global(int ac, char **av)
{
	t_global	*new;

	if (!check_av(ac, av))
		return (NULL);
	new = malloc(sizeof(t_global));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_global));
	new->start_philo = give_utime() + 80;
	new->death = 0;
	new->info = feed_info(ac, av);
	new->tab_fork = creation_tab_fork(new);
	if (!new->tab_fork)
	{
		free(new);
		return (NULL);
	}
	pthread_mutex_init(&new->mutt_print, NULL);
	pthread_mutex_init(&new->mutt_death, NULL);
	new->time_start = give_utime();
	return (new);
}

int	creation_tab_philo(t_global *global)
{
	int	i;
	int	nb_philo;

	i = 0;
	nb_philo = global->info.nb_philo;
	global->tab_philo = malloc(sizeof(t_philo) * nb_philo);
	if (!global->tab_philo)
		return (0);
	memset(global->tab_philo, 0, sizeof(t_philo) * nb_philo);
	while (i < nb_philo)
	{
		global->tab_philo[i].start = global->start_philo;
		global->tab_philo[i].name = i;
		global->tab_philo[i].fork_right = &global->tab_fork[i];
		global->tab_philo[i].fork_left = &global->tab_fork[(i + 1) % nb_philo];
		global->tab_philo[i].global = global;
		global->tab_philo[i].date_of_death = global->start_philo
			+ global->info.time_to_die;
		global->tab_philo[i].info = global->info;
		global->tab_philo[i].number_of_eat = 0;
		i++;
	}
	return (1);
}
