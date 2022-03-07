/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mini_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:52:20 by bsavinel          #+#    #+#             */
/*   Updated: 2022/03/01 15:43:47 by bsavinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n')
		return (1);
	else if (c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

size_t	give_utime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((size_t)time.tv_sec * 1000 + (size_t)time.tv_usec / 1000);
}

void	_usleep(size_t time, t_philo *philo)
{
	size_t	sleep;

	sleep = give_utime() + time;
	if (sleep > 0)
	{
		while (give_utime() / 100 < sleep / 100 && check_death(philo,
				&philo->global->mutt_death))
			usleep(100);
		while (give_utime() < sleep && check_death(philo,
				&philo->global->mutt_death))
			usleep(10);
	}
}
