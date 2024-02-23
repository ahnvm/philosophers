/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argcontrols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <ahmetabdullahcan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:39:00 by acan              #+#    #+#             */
/*   Updated: 2023/12/15 19:53:59 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_all_numeric(char **av)
{
	int	argnum;
	int	charnum;

	argnum = 1;
	while (av[argnum])
	{
		if (*av[argnum] == 0)
			return (0);
		charnum = 0;
		while (av[argnum][charnum])
		{
			if (av[argnum][charnum] < '0' || av[argnum][charnum] > '9')
				return (0);
			charnum++;
		}
		argnum++;
	}
	return (1);
}

int	allargcontrols(int ac, char **av)
{
	int	m_count;

	if (ac == 5 || ac == 6)
	{
		if (!(is_all_numeric(av)))
		{
			return (11);
		}
		if (ac == 6)
		{
			m_count = my_atoi(av[5]);
			if (m_count == 0)
			{
				return (5);
			}
		}
	}
	else
	{
		return (10);
	}
	return (0);
}
