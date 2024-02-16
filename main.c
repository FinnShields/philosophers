/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:12:06 by fshields          #+#    #+#             */
/*   Updated: 2024/02/13 07:16:41 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo	philos	[MAX_PHILO];
	t_data	data;

	if (argc < 5 || argc > 6)
		return (write(2, "error\n", 6));
	if (check_input(argc, argv) != 0)
		return (1);
	if (init_data(&data, argc, argv) != 0)
		return (1);
	if (init_philos(&data, &philos[0]) != 0)
		return (1);
	if (create_threads(&philos[0]) != 0)
		return (write(2, "thread creation error\n", 22));
	destroy_all(&philos[0]);
}
