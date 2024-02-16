/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:14:35 by fshields          #+#    #+#             */
/*   Updated: 2024/02/13 06:55:03 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	ft_isblank(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	else if (c == '\f' || c == '\r' || c == '\n')
		return (1);
	else
		return (0);
}

static int	overflow(int sign)
{
	if (sign == 1)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	long int	rtn;
	long int	prev;
	int			sign;

	i = 0;
	rtn = 0;
	sign = 1;
	while (ft_isblank(str[i]) == 1)
		i ++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i ++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		prev = rtn;
		rtn = (10 * rtn) + (str[i ++] - '0');
		if (rtn < 0 || prev > rtn)
			return (overflow(sign));
	}
	return (rtn * sign);
}

int	check_input(int argc, char *argv[])
{
	int	philos;

	philos = ft_atoi(argv[1]);
	if (philos <= 0 || philos > MAX_PHILO || !check_num(argv[1]))
		return (write(2, "Invalid number of philosophers\n", 31));
	if (ft_atoi(argv[2]) < 0 || !check_num(argv[2]))
		return (write(2, "Invalid time to die\n", 20));
	if (ft_atoi(argv[3]) < 0 || !check_num(argv[3]))
		return (write(2, "Invalid time to eat\n", 20));
	if (ft_atoi(argv[4]) < 0 || !check_num(argv[4]))
		return (write(2, "Invalid time to sleep\n", 22));
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) < 0 || !check_num(argv[5]))
			return (write(2, "Invalid eat requirement\n", 24));
	}
	return (0);
}

int	check_for_death(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->dead_flag == 1)
	{
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}
