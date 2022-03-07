/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:50:45 by bsavinel          #+#    #+#             */
/*   Updated: 2022/03/03 11:25:50 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_global	global;
	int			retour;

	retour = create_global(ac, av, &global);
	if (!retour)
		return (exit_no_arg());
	retour = launch_philo(&global);
	if (retour)
	{
		sem_post(global.sem_start);
		while (waitpid(-1, NULL, 0) > 0)
			;
		good_end(&global);
	}
	return (0);
}
