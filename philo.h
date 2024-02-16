/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:13:08 by fshields          #+#    #+#             */
/*   Updated: 2024/02/13 07:36:29 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

# define MAX_PHILO 200

typedef struct s_data
{
	int				num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				max_meals;
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
}					t_data;

typedef struct s_philo
{
	int				id;
	size_t			start_time;
	size_t			last_ate;
	int				times_eaten;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	eating;
	pthread_t		thread;
	t_data			*data;
}					t_philo;

//utils1.c
int		ft_atoi(const char *str);
int		check_input(int argc, char *argv[]);
int		check_for_death(t_data *data);

//utils2.c
size_t	get_time_ms(void);
void	ft_usleep(size_t time_ms);
void	print_message(char *str, t_philo *philo);
int		destroy_all(t_philo *philo);
int		check_num(char *str);

//init.c
int		init_data(t_data *data, int argc, char *argv[]);
int		init_philos(t_data *data, t_philo *philos);

//philo_routine.c
void	*p_routine(void *arg);

//monitor.c
void	*monitor_loop(void *arg);

//threads.c
int		create_threads(t_philo *philos);

#endif