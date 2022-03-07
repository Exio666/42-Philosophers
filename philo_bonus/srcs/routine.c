/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 08:50:28 by bsavinel          #+#    #+#             */
/*   Updated: 2022/03/03 14:33:05 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_sleep(t_philo *philo)
{
	printer_sem(philo, philo->global->print, philo->name, SLEEP);
	_usleep(philo->info.time_to_sleep, philo->global);
	if (give_utime() > philo->date_of_death)
		modifier_death(philo);
	printer_sem(philo, philo->global->print, philo->name, THINK);
	_usleep(philo->info.med_time_think + 5, philo->global);
	start_eat(philo);
}

void	start_eat(t_philo *philo)
{
	if (give_utime() > philo->date_of_death)
		modifier_death(philo);
	take_fork(philo);
	if (give_utime() > philo->date_of_death)
		modifier_death(philo);
	if (check_death(philo))
	{
		printer_sem(philo, philo->global->print, philo->name, EAT);
		_usleep(philo->info.time_to_eat, philo->global);
	}
	if (give_utime() > philo->date_of_death)
		modifier_death(philo);
	else
	{
		philo->number_of_eat += 1;
		philo->date_of_death = give_utime() + philo->info.time_to_die;
	}
	drop_fork(philo);
	if (check_death(philo) && philo->number_of_eat != philo->info.number_eat)
		start_sleep(philo);
}

void	routine(t_global global)
{
	global.philo.global = &global;
	while (global.sem_start->__align == 0)
		;
	global.philo.date_of_death = give_utime() + global.philo.info.time_to_die;
	if (global.philo.name % 2 == 1)
		_usleep(global.philo.info.time_to_eat - 10, global.philo.global);
	start_eat(&global.philo);
	sem_close(global.death);
	sem_close(global.print);
	sem_close(global.fork);
	sem_close(global.look_fork);
	sem_close(global.sem_start);
}
