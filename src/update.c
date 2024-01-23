/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:37:21 by ggalon            #+#    #+#             */
/*   Updated: 2024/01/23 17:37:21 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	update_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_time);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->m_time);
}

void	update_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_meal);
	philo->eated++;
	if (philo->eated >= philo->data->nbr_meal)
		philo->full = true;
	pthread_mutex_unlock(&philo->m_meal);
}

void	update_end(t_data *data)
{
	pthread_mutex_lock(&data->m_end);
	data->end = true;
	pthread_mutex_unlock(&data->m_end);
}
