/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acan <ahmetabdullahcan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:29:07 by acan              #+#    #+#             */
/*   Updated: 2023/12/15 20:27:37 by acan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define FORK "  has taken a fork\n"
# define EAT "  is eating\n"
# define SLEEP "  is sleeping\n"
# define THINK "  is thinking\n"
# define DEAD "  is dead\n"

typedef struct s_philo
{
	struct s_data	*p_data;
	int				philo_id;
	int				m_count;
	long long		last_eat;
	pthread_t		thread;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
}					t_philo;

typedef struct s_data
{
	int				philo_eat;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				die_flag;
	long int		t_start;
	int				full_philo_count;
	pthread_mutex_t	dead;
	pthread_mutex_t	meallock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printmutex;
	t_philo			*philo;
}					t_data;

int					my_atoi(char *str);
int					allargcontrols(int ac, char **av);
int					ft_print(t_data *data, t_philo *philo, char *str);
int					check_death(t_philo *philo);
long long			timestamp(void);
void				thread_creating(t_data *data);
int					eat(t_philo *philo);
int					ft_sleep(t_philo *philo, long long sleeptime);
int					p_sleep(t_philo *philo);
void				unlock_forks(t_data *data);

#endif