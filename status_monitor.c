/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:43:38 by fshields          #+#    #+#             */
/*   Updated: 2024/02/13 06:57:06 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_dead(t_philo *philo)
{
	size_t	current_time;

	pthread_mutex_lock(&philo->eating);
	current_time = get_time_ms();
	if (current_time - philo->last_ate >= philo->data->time_to_die)
	{
		print_message("died", philo);
		pthread_mutex_unlock(&philo->eating);
		return (1);
	}
	pthread_mutex_unlock(&philo->eating);
	return (0);
}

static void	set_dead_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	philo->data->dead_flag = 1;
	pthread_mutex_unlock(&philo->data->dead_lock);
}

static int	any_death_yet(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->num_of_philos)
	{
		if (philo_dead(&philo[i]))
		{
			set_dead_flag(philo);
			return (1);
		}
	}
	return (0);
}

static int	check_all_full(t_philo *philo)
{
	int	i;

	i = -1;
	if (philo->data->max_meals == -1)
		return (0);
	while (++i < philo->data->num_of_philos)
	{
		pthread_mutex_lock(&philo[i].eating);
		if (philo[i].times_eaten < philo->data->max_meals)
		{
			pthread_mutex_unlock(&philo[i].eating);
			return (0);
		}
		pthread_mutex_unlock(&philo[i].eating);
	}
	set_dead_flag(philo);
	return (1);
}

void	*monitor_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		if (check_all_full(philo) || any_death_yet(philo))
			break ;
	}
	return (arg);
}
