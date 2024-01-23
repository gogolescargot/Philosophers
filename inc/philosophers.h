/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:43:10 by ggalon            #+#    #+#             */
/*   Updated: 2024/01/18 15:43:10 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	bool			full;
	int				eated;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	m_meal;
	pthread_mutex_t	m_time;
	size_t			last_meal;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				nbr_philos;
	int				nbr_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_end;
	pthread_t		monitor;
	bool			end;
	t_philo			*philos;
}	t_data;

void	init_data(t_data *data, char **argv);
void	init_philos(t_data *data);

void	*monitor(void *arg);
bool	check_dead(t_philo *philo);
bool	check_full(t_data *data);

void	*life(void *arg);
void	life_solo(t_philo *philo);
void	eat(t_philo *philo);
void	take_fork(t_philo *philo);

int		ft_atoi(const char *nptr);
void	ft_usleep(size_t time);
size_t	get_time(void);
bool	get_bool(pthread_mutex_t *mutex, bool *src);
void	print(t_philo *philo, int message);

void	update_time(t_philo *philo);
void	update_meal(t_philo *philo);
void	update_end(t_data *data);

#endif