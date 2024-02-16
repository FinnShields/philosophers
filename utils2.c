/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:59:44 by fshields          #+#    #+#             */
/*   Updated: 2024/02/13 07:14:58 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t time_ms)
{
	size_t	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < time_ms)
		usleep(500);
}

void	print_message(char *str, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->write_lock);
	time = get_time_ms() - philo->start_time;
	if (!check_for_death(philo->data))
		printf("%zu %i %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write_lock);
}

int	destroy_all(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->num_of_philos)
	{
		pthread_mutex_destroy(&philo->r_fork);
		pthread_mutex_destroy(&philo->eating);
		philo->l_fork = NULL;
	}
	pthread_mutex_destroy(&philo->data->dead_lock);
	pthread_mutex_destroy(&philo->data->write_lock);
	return (1);
}

int	check_num(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str ++;
	}
	return (1);
}
