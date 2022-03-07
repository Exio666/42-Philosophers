/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:35:29 by bsavinel          #+#    #+#             */
/*   Updated: 2022/03/03 13:46:41 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_int(char *str)
{
	int			len;
	int			i;
	long int	nb;

	i = 0;
	len = ft_strlen(str);
	while (str[i] == '0' && i < len - 1)
		i++;
	len = ft_strlen(&str[i]);
	if (len > 10 || len <= 0)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	nb = ft_atol(str);
	if (nb < 0 || nb > 2147483647)
		return (0);
	return (1);
}

long int	ft_atol(const char *nptr)
{
	long int	neg;
	int			i;
	long int	nb;

	i = 0;
	nb = 0;
	neg = 1;
	while (ft_isspace(nptr[i]) == 1)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while (nptr[i] <= '9' && nptr[i] >= '0')
	{
		nb = nb * 10 + nptr[i] - 48;
		i++;
	}
	if (neg == -1)
		nb = -nb;
	return (nb);
}

void	printer_sem(t_philo *philo, sem_t *print, int name, char *str)
{
	sem_wait(print);
	if (check_death(philo))
		printf("%05li %i %s\n", give_utime() - philo->start, name + 1, str);
	sem_post(print);
}

void	take_fork(t_philo *philo)
{
	int	take;

	take = 0;
	while (give_utime() <= philo->date_of_death)
	{
		sem_wait(philo->global->look_fork);
		if (philo->global->fork->__align >= 2)
		{
			take = 1;
			sem_wait(philo->global->fork);
			sem_wait(philo->global->fork);
			sem_post(philo->global->look_fork);
			break ;
		}
		sem_post(philo->global->look_fork);
	}
	if (give_utime() > philo->date_of_death)
		modifier_death(philo);
	if (take == 1)
	{
		printer_sem(philo, philo->global->print, philo->name, TAKE_FORK);
		printer_sem(philo, philo->global->print, philo->name, TAKE_FORK);
	}
}

void	drop_fork(t_philo *philo)
{
	sem_wait(philo->global->look_fork);
	sem_post(philo->global->fork);
	sem_post(philo->global->fork);
	sem_post(philo->global->look_fork);
}
