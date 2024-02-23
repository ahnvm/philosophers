/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <ahmetabdullahcan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:48:49 by acan              #+#    #+#             */
/*   Updated: 2023/12/15 20:16:14 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat_finish(t_data *data)
{
	pthread_mutex_lock(&data->meallock);
	if (data->full_philo_count == data->n_philo)
	{
		pthread_mutex_unlock(&data->meallock);
		return (1);
	}
	pthread_mutex_unlock(&data->meallock);
	return (0);
}

static void	finish_control(t_data *data)
{
	int	loop;

	loop = 0;
	while (1)
	{
		if (loop == data->n_philo)
			loop = 0;
		pthread_mutex_lock(&data->dead);
		if ((timestamp() - (data->philo[loop]).last_eat) > data->t_die)
		{
			if (data->die_flag == 0)
				printf("%llu %d %s", timestamp() - data->t_start,
					data->philo[loop].philo_id, DEAD);
			data->die_flag = 1;
			unlock_forks(data);
			pthread_mutex_unlock(&data->dead);
			break ;
		}
		pthread_mutex_unlock(&data->dead);
		if (eat_finish(data) == 1)
			break ;
		loop++;
	}
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->p_data->meallock);
	if (philo->p_data->full_philo_count == philo->p_data->n_philo)
	{
		pthread_mutex_unlock(&philo->p_data->meallock);
		return (2);
	}
	pthread_mutex_unlock(&philo->p_data->meallock);
	pthread_mutex_lock(&philo->p_data->dead);
	if (philo->p_data->die_flag == 1)
	{
		pthread_mutex_unlock(&philo->p_data->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->p_data->dead);
	return (0);
}

void	*life_cycle(void *tmp_philo)
{
	t_philo	*philo;

	philo = (t_philo *)tmp_philo;
	philo->last_eat = timestamp();
	while (1)
	{
		pthread_mutex_lock(&philo->p_data->meallock);
		if (philo->p_data->full_philo_count == philo->p_data->n_philo)
		{
			pthread_mutex_unlock(&philo->p_data->meallock);
			return (0);
		}
		pthread_mutex_unlock(&philo->p_data->meallock);
		if (check_death(philo) != 0)
			return (0);
		if (eat(philo) != 0)
			return (0);
		if (p_sleep(philo))
			return (0);
	}
	return (0);
}

void	thread_creating(t_data *data)
{
	int	loop;

	loop = 0;
	data->t_start = timestamp();
	while (loop < data->n_philo)
	{
		pthread_create(&data->philo[loop].thread, NULL, &life_cycle,
			&data->philo[loop]);
		loop++;
		usleep(50);
	}
	finish_control(data);
	loop = 0;
	while (loop < data->n_philo)
	{
		pthread_join(data->philo[loop].thread, NULL);
		loop++;
	}
}
