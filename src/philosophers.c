/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:43:12 by ggalon            #+#    #+#             */
/*   Updated: 2024/01/18 15:43:12 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	printf("prends la fourchette gauche\n");
	pthread_mutex_lock(philo->r_fork);
	printf("prends la fourchette droite\n");
}

void	eat(t_philo *philo)
{
	printf("je mange\n");
	philo->eated++;
	usleep(philo->time_to_eat);
	pthread_mutex_unlock(&(philo->l_fork));
	pthread_mutex_unlock(philo->r_fork);
	usleep(philo->time_to_sleep);
	printf("je réfléchis\n");
}

void	*life(void *arg)
{
	
	t_philo *philo = (t_philo *)arg;

	printf("je suis le thread %d\n", philo->id);
	take_fork(philo);
	eat(philo);
	return (NULL);
}

void init_philos(t_data *data)
{
	int i;

	data->philos = malloc(sizeof(t_philo) * (data->nbr_philos));
	i = -1;
	while (++i < data->nbr_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].r_fork = NULL;
		data->philos[i].eated = 0	;
		data->philos[i].dead= false;
		data->philos[i].last_meal = 0;
		data->philos[i].time_to_die = data->time_to_die;
		data->philos[i].time_to_eat = data->time_to_eat;
		data->philos[i].time_to_sleep = data->time_to_sleep;
		pthread_mutex_init(&data->philos[i].l_fork, NULL);
		data->philos[i].r_fork = &data->philos[(i + 1) % data->nbr_philos].l_fork;
		pthread_create(&(data->philos[i].thread), NULL, life, &data->philos[i]);
	}
	i = -1;
	while (++i < data->nbr_philos)
		pthread_join(data->philos[i].thread, NULL);
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
	init_philos(data);
}

bool	check_param(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (ft_atoi(argv[i]) <= 0)
			return (false);
	}
	return (true);
}

void	destroy(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philos)
		pthread_mutex_destroy(&data->philos->l_fork);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (printf("Error: Incorrect number of parameters\n"), 1);
	if (!check_param(argv))
		return (printf("Error: Incorrect parameter\n"), 1);
	init_data(&data, argv);
	destroy(&data);
	return (0);
}
