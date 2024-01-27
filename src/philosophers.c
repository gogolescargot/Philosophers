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

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (printf("Error: Incorrect number of parameters\n"), 1);
	if (!check_param(argv))
		return (printf("Error: Incorrect parameter\n"), 1);
	init_data(&data, argv);
	if (!data.philos)
		return (printf("Malloc error\n"), 1);
	free(data.philos);
	return (0);
}
