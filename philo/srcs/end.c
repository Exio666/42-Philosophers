/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:00:41 by bsavinel          #+#    #+#             */
/*   Updated: 2022/03/02 16:33:28 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	good_end(t_global *global)
{	
	fusion_philo(global, global->info.nb_philo);
	destruc_fork(global, global->info.nb_philo);
	free(global->tab_philo);
	free(global->tab_pthread);
	free(global);
	return (1);
}

int	exit_no_tab_philo(t_global *global)
{
	fusion_philo(global, global->info.nb_philo);
	destruc_fork(global, global->info.nb_philo);
	free(global);
	return (0);
}

int	exit_no_arg(void)
{
	printf("Argument is not valiable\n");
	printf("Please make sur you have lunch with : %s\n", LIST_OF_ARG);
	return (0);
}

int	exit_time_or_mutex(void)
{
	printf("Probleme with the time or one malloc fail");
	return (0);
}
