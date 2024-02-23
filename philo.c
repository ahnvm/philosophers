/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <ahmetabdullahcan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:50:07 by acan              #+#    #+#             */
/*   Updated: 2023/12/15 20:27:53 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init(t_philo *philo, t_data *data)
{
	int	loop_number;

	loop_number = 0;
	while (loop_number < data->n_philo)
	{
		philo[loop_number].p_data = data;
		philo[loop_number].fork_l = &data->forks[loop_number];
		philo[loop_number].fork_r = &data->forks[(loop_number + 1)
			% data->n_philo];
		pthread_mutex_init(philo[loop_number].fork_l, NULL);
		pthread_mutex_init(philo[loop_number].fork_r, NULL);
		philo[loop_number].last_eat = 0;
		philo[loop_number].m_count = philo[loop_number].p_data->n_eat;
		philo[loop_number].philo_id = loop_number + 1;
		loop_number++;
	}
}

static int	data_init(t_data *data, int ac, char **av)
{
	int	n_ph;

	data->n_philo = my_atoi(av[1]);
	data->t_die = my_atoi(av[2]);
	data->t_eat = my_atoi(av[3]);
	data->t_sleep = my_atoi(av[4]);
	data->die_flag = 0;
	data->full_philo_count = 0;
	data->t_start = 0;
	data->n_eat = -1;
	if (ac == 6)
		data->n_eat = my_atoi(av[5]);
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->printmutex, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->n_philo));
	if (!data->forks)
		return (1);
	n_ph = 0;
	while (n_ph < data->n_philo)
		pthread_mutex_init(&data->forks[n_ph++], NULL);
	pthread_mutex_init(&data->meallock, NULL);
	data->philo = (t_philo *)malloc(sizeof(t_philo) * (data->n_philo));
	if (!data->philo)
		return (3);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		errorcode;

	errorcode = allargcontrols(ac, av);
	if (errorcode != 0)
	{
		if (errorcode == 5)
			return (0);
		write(2, "Error\n", 6);
		return (errorcode);
	}
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (13);
	if (data_init(data, ac, av))
		return (13);
	philo_init(data->philo, data);
	thread_creating(data);
	return (0);
}
