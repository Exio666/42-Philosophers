/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_and_drop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:56:05 by bsavinel          #+#    #+#             */
/*   Updated: 2022/03/03 15:11:22 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_right(t_philo *philo)
{
	while (give_utime() < philo->date_of_death)
	{
		pthread_mutex_lock(&philo->fork_right->fork);
		if (philo->fork_right->take == 0)
		{
			philo->fork_right->take = 1;
			pthread_mutex_unlock(&philo->fork_right->fork);
			break ;
		}
		pthread_mutex_unlock(&philo->fork_right->fork);
	}
	printer_mutex(philo, &philo->global->mutt_print, philo->name, TAKE_FORK);
}

void	take_left(t_philo *philo)
{
	while (give_utime() <= philo->date_of_death + 1)
	{
		pthread_mutex_lock(&philo->fork_left->fork);
		if (philo->fork_left->take == 0)
		{
			philo->fork_left->take = 1;
			pthread_mutex_unlock(&philo->fork_left->fork);
			break ;
		}
		pthread_mutex_unlock(&philo->fork_left->fork);
	}
	if (give_utime() > philo->date_of_death)
		modifier_death(philo, &philo->global->mutt_death, -1);
	printer_mutex(philo, &philo->global->mutt_print, philo->name, TAKE_FORK);
}

void	take_fork(t_philo *philo)
{
	take_right(philo);
	take_left(philo);
}

void	drop_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_right->fork);
	philo->fork_right->take = 0;
	pthread_mutex_unlock(&philo->fork_right->fork);
	pthread_mutex_lock(&philo->fork_left->fork);
	philo->fork_left->take = 0;
	pthread_mutex_unlock(&philo->fork_left->fork);
}
