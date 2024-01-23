/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:09:12 by ggalon            #+#    #+#             */
/*   Updated: 2024/01/22 17:09:12 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

bool	check_full(t_data *data)
{
	int		i;

	i = -1;
	if (data->nbr_meal == -1)
		return (false);
	pthread_mutex_lock(&data->philos->m_meal);
	while (++i < data->nbr_philos && !data->end)
	{
		if (!data->philos[i].full)
		{
			pthread_mutex_unlock(&data->philos->m_meal);
			return (false);
		}
	}
	pthread_mutex_unlock(&data->philos->m_meal);
	return (true);
}

bool	check_dead(t_philo *philo)
{
	bool	dead;

	dead = false;
	pthread_mutex_lock(&philo->m_time);
	if (get_time() - philo->last_meal >= philo->data->time_to_die)
		dead = true;
	pthread_mutex_unlock(&philo->m_time);
	return (dead);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = -1;
	while (!data->end)
	{
		while (++i < data->nbr_philos && !data->end)
		{
			if (check_dead(&data->philos[i]))
			{
				print(&data->philos[i], 4);
				update_end(data);
				return (NULL);
			}
			if (check_full(data))
			{
				update_end(data);
				return (NULL);
			}
		}
		i = -1;
	}
	return (NULL);
}
