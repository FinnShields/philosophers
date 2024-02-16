/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:21:37 by fshields          #+#    #+#             */
/*   Updated: 2024/02/13 06:57:19 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	sleep_and_think(t_philo *philo)
{
	print_message("is sleeping", philo);
	ft_usleep(philo->data->time_to_sleep);
	print_message("is thinking", philo);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork);
	print_message("has taken a fork", philo);
	if (philo->data->num_of_philos == 1)
	{
		ft_usleep(philo->data->time_to_die);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo);
	pthread_mutex_lock(&philo->eating);
	print_message("is eating", philo);
	philo->last_ate = get_time_ms();
	philo->times_eaten ++;
	pthread_mutex_unlock(&philo->eating);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	*p_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!check_for_death(philo->data))
	{
		eat(philo);
		sleep_and_think(philo);
	}
	return (arg);
}
