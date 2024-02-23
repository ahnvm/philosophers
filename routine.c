/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <ahmetabdullahcan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:13:44 by acan              #+#    #+#             */
/*   Updated: 2023/12/15 20:27:58 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	p_sleep(t_philo *philo)
{
	if (ft_print(philo->p_data, philo, SLEEP))
		return (1);
	if (ft_sleep(philo, philo->p_data->t_sleep))
		return (1);
	if (ft_print(philo->p_data, philo, THINK))
		return (1);
	return (0);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	ft_print(philo->p_data, philo, FORK);
	pthread_mutex_lock(philo->fork_r);
	ft_print(philo->p_data, philo, FORK);
	pthread_mutex_lock(&philo->p_data->dead);
	philo->last_eat = timestamp();
	pthread_mutex_unlock(&philo->p_data->dead);
	ft_print(philo->p_data, philo, EAT);
	if (ft_sleep(philo, philo->p_data->t_eat))
		return (1);
	pthread_mutex_lock(&philo->p_data->meallock);
	philo->m_count--;
	if (philo->m_count == 0)
	{
		philo->p_data->full_philo_count++;
		pthread_mutex_unlock(&philo->p_data->meallock);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		return (1);
	}
	pthread_mutex_unlock(&philo->p_data->meallock);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	return (0);
}
