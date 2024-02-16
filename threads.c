/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:27:12 by fshields          #+#    #+#             */
/*   Updated: 2024/02/13 07:15:53 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_philo *philos)
{
	pthread_t	monitor;
	int			i;

	i = -1;
	if (pthread_create(&monitor, NULL, &monitor_loop, philos) != 0)
		return (destroy_all(philos));
	while (++i < philos->data->num_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &p_routine, \
			&philos[i]) != 0)
			return (destroy_all(philos));
	}
	i = -1;
	if (pthread_join(monitor, NULL) != 0)
		return (destroy_all(philos));
	while (++i < philos->data->num_of_philos)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (destroy_all(philos));
	}
	return (0);
}
