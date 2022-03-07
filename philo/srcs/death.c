/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:35:17 by bsavinel          #+#    #+#             */
/*   Updated: 2022/03/01 15:49:35 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo, pthread_mutex_t *muttex)
{
	int	condition;

	condition = 1;
	pthread_mutex_lock(muttex);
	if (philo->global->death == -1)
		condition = 0;
	pthread_mutex_unlock(muttex);
	return (condition);
}

int	check_death_global(t_global *global, pthread_mutex_t *muttex)
{
	int	condition;

	condition = 1;
	pthread_mutex_lock(muttex);
	if (global->death == -1 || global->death == global->info.nb_philo)
		condition = 0;
	pthread_mutex_unlock(muttex);
	return (condition);
}

void	modifier_death(t_philo *philo, pthread_mutex_t *muttex, int value)
{
	if (value == -1)
		printer_mutex(philo, &philo->global->mutt_print, philo->name, "died");
	pthread_mutex_lock(muttex);
	if (value == 1 && philo->global->death != -1)
		philo->global->death += 1;
	if (value == -1)
		philo->global->death = -1;
	pthread_mutex_unlock(muttex);
}
