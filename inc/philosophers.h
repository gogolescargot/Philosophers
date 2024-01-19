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

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	bool			dead;
	int				eated;
	size_t			last_meal;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
}	t_philo;

typedef struct s_data
{
	t_philo	*philos;
	int		nbr_philos;
	int		nbr_meal;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	
}	t_data;

int	ft_atoi(const char *nptr);

#endif