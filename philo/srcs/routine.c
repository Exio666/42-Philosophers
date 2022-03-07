/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 08:50:28 by bsavinel          #+#    #+#             */
/*   Updated: 2022/03/03 15:07:30 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_sleep(t_philo *philo)
{
	printer_mutex(philo, &philo->global->mutt_print, philo->name, SLEEP);
	_usleep(philo->info.time_to_sleep, philo);
	if (give_utime() > philo->date_of_death)
		modifier_death(philo, &philo->global->mutt_death, -1);
	printer_mutex(philo, &philo->global->mutt_print, philo->name, THINK);
	_usleep(1, philo);
	start_eat(philo);
}

void	start_eat(t_philo *philo)
{
	if (give_utime() > philo->date_of_death)
		modifier_death(philo, &philo->global->mutt_death, -1);
	take_fork(philo);
	if (give_utime() > philo->date_of_death)
		modifier_death(philo, &philo->global->mutt_death, -1);
	if (check_death(philo, &philo->global->mutt_death))
	{
		printer_mutex(philo, &philo->global->mutt_print, philo->name, EAT);
		_usleep(philo->info.time_to_eat, philo);
	}
	if (give_utime() > philo->date_of_death)
		modifier_death(philo, &philo->global->mutt_death, -1);
	else
	{
		philo->number_of_eat += 1;
		philo->date_of_death = give_utime() + philo->info.time_to_die;
	}
	drop_fork(philo);
	if (philo->number_of_eat != philo->info.number_eat)
		modifier_death(philo, &philo->global->mutt_death, 1);
	if (check_death(philo, &philo->global->mutt_death)
		&& philo->number_of_eat != philo->info.number_eat)
		start_sleep(philo);
}

void	*routine(void *structure)
{
	t_philo	*philo;

	philo = structure;
	while (give_utime() < philo->start)
		;
	philo->date_of_death = give_utime() + philo->info.time_to_die;
	if (philo->name % 2 == 1)
		_usleep(philo->info.time_to_eat - 10, philo);
	start_eat(philo);
	return (NULL);
}

int	launch_philo(t_global *global)
{
	int	i;
	int	err;

	i = 0;
	global->tab_pthread = malloc(sizeof(pthread_t) * global->info.nb_philo);
	if (!global->tab_pthread)
		return (-1);
	while (i < global->info.nb_philo)
	{
		err = pthread_create(&global->tab_pthread[i], NULL, &routine,
				&global->tab_philo[i]);
		if (err != 0)
			return (i);
		i++;
	}
	return (0);
}
