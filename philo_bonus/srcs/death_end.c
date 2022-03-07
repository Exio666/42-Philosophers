/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:00:41 by bsavinel          #+#    #+#             */
/*   Updated: 2022/03/03 15:23:27 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_death(t_philo *philo)
{
	int	condition;

	condition = 1;
	if (philo->global->death->__align != 0)
		condition = 0;
	return (condition);
}

void	modifier_death(t_philo *philo)
{
	sem_wait(philo->global->print);
	if (check_death(philo))
		printf("%05li %i %s\n", give_utime() - philo->start,
			philo->name + 1, "died");
	sem_post(philo->global->death);
	sem_post(philo->global->print);
}

int	good_end(t_global *global)
{	
	sem_close(global->death);
	sem_close(global->print);
	sem_close(global->fork);
	sem_close(global->look_fork);
	sem_close(global->sem_start);
	return (1);
}

int	exit_no_arg(void)
{
	printf("Argument is not valiable\n");
	printf("Please make sur you have lunch with : %s\n", LIST_OF_ARG);
	return (0);
}
