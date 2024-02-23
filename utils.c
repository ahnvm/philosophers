/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <ahmetabdullahcan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:45:57 by acan              #+#    #+#             */
/*   Updated: 2023/12/15 20:28:30 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	my_atoi(char *str)
{
	int	count;
	int	sign;
	int	result;

	count = 0;
	result = 0;
	sign = 1;
	while ((str[count] >= 9 && str[count] <= 13) || str[count] == ' ')
		count++;
	if (str[count] == '-' || str[count] == '+')
	{
		if (str[count] == '-')
			sign = -1;
		count++;
	}
	while (str[count] >= '0' && str[count] <= '9')
	{
		result = (result * 10) + str[count] - '0';
		count++;
	}
	return (sign * result);
}

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_print(t_data *data, t_philo *philo, char *str)
{
	pthread_mutex_lock(&data->printmutex);
	if (check_death(philo) != 0)
	{
		pthread_mutex_unlock(&data->printmutex);
		return (1);
	}
	printf("%llu %d %s", (timestamp() - data->t_start), philo->philo_id, str);
	pthread_mutex_unlock(&data->printmutex);
	return (0);
}

int	ft_sleep(t_philo *philo, long long sleeptime)
{
	long long	loop;

	loop = timestamp() + sleeptime;
	while (loop > timestamp())
	{
		usleep(200);
		if (check_death(philo) == 1)
			return (1);
	}
	return (0);
}

void	unlock_forks(t_data *data)
{
	int	loop;

	loop = 0;
	while (loop < data->n_philo)
	{
		pthread_mutex_unlock(&data->forks[loop]);
		loop++;
	}
}
