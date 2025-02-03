/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:27:49 by nuno              #+#    #+#             */
/*   Updated: 2025/01/28 22:44:40 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	get_arg(t_philo_data *data, int arc, char **arv);

int	main(int arc, char **arv)
{
	t_philo_data	*data;
	t_philo		*philosophers;

	if ( arc == 5 || arc == 6)
	{
		data = initiate_data();
		get_arg(data, arc, arv);
		creating_philos(data);
		//correr o programa
	}
	else
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	return (0);
}

static void	get_arg(t_philo_data *data, int arc, char **arv)
{
	data->num_of_philos = ft_atoi(arv[1]);
	data->num_of_forks = data->num_of_philos;
	data->time_to_die = ft_atoi(arv[2]);
	data->time_to_eat = ft_atoi(arv[3]);
	data->time_to_sleep = ft_atoi(arv[4]);
	if (arc == 6)
		data->num_must_eat = ft_atoi(arv[5]);
	else
		data->num_must_eat = -1;
}