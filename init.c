/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:21:55 by fshields          #+#    #+#             */
/*   Updated: 2024/02/13 07:12:41 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char *argv[])
{
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = (size_t) ft_atoi(argv[2]);
	data->time_to_eat = (size_t) ft_atoi(argv[3]);
	data->time_to_sleep = (size_t) ft_atoi(argv[4]);
	if (argc == 5)
		data->max_meals = -1;
	else
		data->max_meals = ft_atoi(argv[5]);
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (write(2, "mutex error\n,", 12));
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (write(2, "mutex error\n,", 12));
	return (0);
}

int	init_philos(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].start_time = get_time_ms();
		philos[i].last_ate = philos[i].start_time;
		philos[i].times_eaten = 0;
		if (pthread_mutex_init(&philos[i].r_fork, NULL) != 0)
			return (write(2, "mutex error\n,", 12));
		if (i == 0 && data->num_of_philos != 1)
			philos[i].l_fork = &philos[data->num_of_philos - 1].r_fork;
		else if (data->num_of_philos != 1)
			philos[i].l_fork = &philos[i - 1].r_fork;
		else
			philos[i].l_fork = NULL;
		if (pthread_mutex_init(&philos[i].eating, NULL) != 0)
			return (write(2, "mutex error\n,", 12));
		philos[i].data = data;
	}
	return (0);
}
