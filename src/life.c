/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:07:57 by ggalon            #+#    #+#             */
/*   Updated: 2024/01/22 17:07:57 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print(philo, 0);
		pthread_mutex_lock(&philo->l_fork);
		print(philo, 0);
	}
	else
	{
		pthread_mutex_lock(&philo->l_fork);
		print(philo, 0);
		pthread_mutex_lock(philo->r_fork);
		print(philo, 0);
	}
}

void	eat(t_philo *philo)
{
	update_time(philo);
	update_meal(philo);
	print(philo, 1);
	usleep(philo->data->time_to_eat * 1000);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&(philo->l_fork));
	}
	else
	{
		pthread_mutex_unlock(&(philo->l_fork));
		pthread_mutex_unlock(philo->r_fork);
	}
	print(philo, 2);
	usleep(philo->data->time_to_sleep * 1000);
	print(philo, 3);
}

void	life_solo(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	print(philo, 0);
}

void	*life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nbr_philos == 1)
		return (life_solo(philo), NULL);
	if (philo->id % 2 == 0)
		usleep(420);
	while (!philo->data->end)
	{
		take_fork(philo);
		eat(philo);
		if (philo->data->time_to_eat >= philo->data->time_to_sleep)
		{
			usleep((philo->data->time_to_eat
					- philo->data->time_to_sleep + 1) * 1000);
		}
	}
	return (NULL);
}
