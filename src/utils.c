/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:24:31 by ggalon            #+#    #+#             */
/*   Updated: 2024/01/18 18:24:31 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		m;
	long	r;

	i = 0;
	r = 0;
	m = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == 45)
	{
		m = -1;
		i++;
	}
	else if (nptr[i] == 43)
		i++;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		if (r > LONG_MAX / 10)
			return (-1 * (m == 1));
		r = nptr[i++] - 48 + (r * 10);
		if (r < 0)
			return (-1 * (m == 1));
	}
	return (r * m);
}

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

bool	get_bool(pthread_mutex_t *mutex, bool *src)
{
	bool	ret_val;

	pthread_mutex_lock(mutex);
	ret_val = *src;
	pthread_mutex_unlock(mutex);
	return (ret_val);
}

void	ft_usleep(size_t time)
{
	size_t	start;

	start = get_time();
	while (get_time() < start + time)
		usleep(500);
}

void	print(t_philo *philo, int message)
{
	size_t	time;

	time = get_time();
	if (get_bool(&philo->data->m_end, &philo->data->end))
		return ;
	pthread_mutex_lock(&philo->data->m_print);
	printf("%zu %d ", time - philo->data->start_time, philo->id);
	if (message == 0)
		printf("has taken the fork\n");
	else if (message == 1)
		printf("is eating\n");
	else if (message == 2)
		printf("is sleeping\n");
	else if (message == 3)
		printf("is thinking\n");
	else if (message == 4)
		printf("is dead\n");
	pthread_mutex_unlock(&philo->data->m_print);
}
