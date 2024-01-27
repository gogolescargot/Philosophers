/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:10:41 by ggalon            #+#    #+#             */
/*   Updated: 2024/01/22 17:10:41 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	wait_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philos)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(data->monitor, NULL);
}

void	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * (data->nbr_philos));
	if (!data->philos)
		return ;
	i = -1;
	while (++i < data->nbr_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].r_fork = NULL;
		data->philos[i].eated = 0;
		data->philos[i].last_meal = get_time();
		data->philos[i].full = false;
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].l_fork, NULL);
		pthread_mutex_init(&data->philos[i].m_meal, NULL);
		pthread_mutex_init(&data->philos[i].m_time, NULL);
		data->philos[i].r_fork
			= &data->philos[(i + 1) % data->nbr_philos].l_fork;
		pthread_create(&(data->philos[i].thread), NULL, life, &data->philos[i]);
	}
	pthread_create(&(data->monitor), NULL, monitor, data);
	wait_philos(data);
}

void	init_data(t_data *data, char **argv)
{
	data->nbr_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->nbr_meal = ft_atoi(argv[5]);
	else
		data->nbr_meal = -1;
	data->start_time = get_time();
	data->end = false;
	pthread_mutex_init(&data->m_print, NULL);
	pthread_mutex_init(&data->m_end, NULL);
	init_philos(data);
}
